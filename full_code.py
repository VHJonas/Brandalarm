from gpiozero import Button
button = Button(2)  # Initialiseer een knop op pin 2

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
buzzer_pin = 18
GPIO.setup(buzzer_pin, GPIO.OUT)
pwm = GPIO.PWM(buzzer_pin, 0.1) # Initialiseer PWM op pin 18 met frequentie 0.1 Hz

import time

import paho.mqtt.client as mqtt
alarm = "alarm/alarm/trigger"   # Topic om op te abonneren voor alarmactivatie
reset = "alarm/alarm/reset"     # Topic om op te abonneren voor alarmreset

mqtt_broker = "192.168.1.43"
mqtt_port = 1883
mqtt_user = "jonaspi"
mqtt_password ="jonaspi"

alarm_active = False  # Variabele om de status van het alarm bij te houden

def on_connect(client, userdata, flags, rc, properties=None):
    print("Verbonden met code: " + str(rc))  # Toont de verbindingsstatus met de MQTT broker
    client.subscribe(alarm)  # Abonneer op het alarm topic
    client.subscribe(reset)  # Abonneer op het reset topic

def on_message(client, userdata, msg):
    global alarm_active
    topic = msg.topic
    payload = msg.payload.decode("utf-8")

    print(f"Ontvangen bericht: Topic: {topic}, Payload: {payload}")  # Toont ontvangen berichten

    if topic == alarm:
        if payload == "vuur":
            print("FIIIIIIIREEEEEEEEEEE")  # Toont bericht bij alarmactivatie
            alarm_active = True
            pwm.start(50)  # Start de buzzer met 50% duty cycle
        elif payload == "geen vuur":
            print("Geen vuur, alarm uit")  # Toont bericht bij deactivering van het alarm
            alarm_active = False
            pwm.stop()  # Stop de buzzer

mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.username_pw_set(mqtt_user, mqtt_password)
mqttc.connect(mqtt_broker, mqtt_port, 60)  # Verbind met MQTT broker

def check_button():
    if button.is_pressed & alarm_active == True:
        print("Resetknop ingedrukt")  # Toont bericht bij indrukken van de resetknop
        mqttc.publish(reset, "1")  # Publiceer bericht om alarm te resetten

try:
    while True:
        mqttc.loop()  # Blijf MQTT berichten verwerken
        check_button()  # Controleer of de resetknop is ingedrukt
        if alarm_active:
            for freq in range(500, 900, 1):
                if not alarm_active:
                    break
                pwm.ChangeFrequency(freq)  # Verander frequentie van de buzzer bij alarmactivering
                time.sleep(0.01)
        else:
            time.sleep(0.1)  # Wacht tussen lussen

except KeyboardInterrupt:
    mqttc.disconnect()  # Verbreek de verbinding met MQTT broker bij KeyboardInterrupt
    pwm.stop()  # Zet de buzzer uit
    GPIO.cleanup()  # Maak GPIO pinnen schoon
