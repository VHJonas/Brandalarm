#include <WiFi.h>
#include <PubSubClient.h>

// WiFi en MQTT server instellingen
const char* ssid = "Proximus-Home-69D8"; // WiFi SSID
const char* password = "wya7ymxdyzynd";  // WiFi wachtwoord
const char* mqttServer = "192.168.1.43"; // MQTT server IP-adres
const int mqttPort = 1883;               // MQTT server poort
const char* mqttUser = "jonaspi";        // MQTT gebruikersnaam
const char* mqttPassword = "jonaspi";    // MQTT wachtwoord
const char* clientID = "ESP32";          // Client ID voor de ESP32

// WiFi en MQTT client initialisatie
WiFiClient espClient;
PubSubClient client(espClient);

#define FLAME 32  // Aansluiting DO pin van sensor op deze pin
#define LED 33    // Pin voor LED

int status = HIGH; // Globale statusvariabele

void setup() {
  Serial.begin(9600);
  pinMode(FLAME, INPUT);  // Definieer FLAME in
  pinMode(LED, OUTPUT);   // Definieer LED output pin

  // Verbinden met WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Verbinden met WiFi...");
  }
  Serial.println("Verbonden met het WiFi-netwerk");

  // Instellen van de MQTT server
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback); // Voeg de callback functie toe
}

void loop() {
  client.loop();
  while (!client.connected()) {
    Serial.println("Verbinden met MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Verbonden");
      client.subscribe("alarm/alarm/reset"); // Abonneer op het reset topic
    } else {
      Serial.print("Verbinding mislukt, status: ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  int fire = digitalRead(FLAME);  // Lees de FLAME sensor

  // Als er vuur wordt gedetecteerd gaat de noodverlichtings-LED aan en wordt er gepubliceerd dat het alarm aan moet.
  if (fire == HIGH && status == HIGH) {
    digitalWrite(LED, HIGH);  // Zet de LED aan
    Serial.println("Vuur! Vuur!");
    client.publish("alarm/alarm/trigger", "vuur");  // Publiceer bericht "vuur" naar het topic alarm/alarm/trigger
    status = LOW; // Update de status naar LOW om aan te geven dat het alarm is geactiveerd
  }
}

// Callback functie om berichten te verwerken die binnenkomen via MQTT
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Bericht ontvangen op topic: ");
  Serial.print(topic);
  Serial.print(". Bericht: ");
  String messageString;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageString += (char)message[i];
  }
  Serial.println();

  // Als een bericht is ontvangen op het topic alarm/alarm/reset, controleer of het bericht "1" is.
  // Verander de status terug naar HIGH
  if (String(topic) == "alarm/alarm/reset") {
    Serial.print("Reset ontvangen: ");
    if (messageString == "1" && digitalRead(FLAME) == LOW) {
      Serial.println("BINGO");
      client.publish("alarm/alarm/trigger", "geen vuur"); // Stuur bericht "geen vuur"
      status = HIGH; // Update de globale statusvariabele
      digitalWrite(LED, LOW); // Zet de LED uit
    }
  }
}
