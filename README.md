# Branddetectie- en Alarmsysteem

Dit project beschrijft de ontwikkeling van een branddetectie- en alarmsysteem met behulp van een ESP32 microcontroller en een Raspberry Pi. Het systeem maakt gebruik van een KY-026 branddetectiemodule om brand te detecteren en een KY-006 passieve buzzermodule om een alarm te activeren. De communicatie tussen de ESP32 en de Raspberry Pi verloopt via het MQTT-protocol. Bovendien wordt Grafana gebruikt om de status en meldingen van het systeem visueel te monitoren en te analyseren.

## Inhoudsopgave

- [Benodigdheden](#benodigdheden)
- [Architectuur](#architectuur)
- [Elektrische Schema's](#elektrische-schema's)
- [C++ Codes](#c-codes)
- [Documentatie](#documentatie)
- [Installatie](#installatie)
- [Gebruik](#gebruik)
- [Contributie](#contributie)
- [Licentie](#licentie)

## Benodigdheden

- ESP32 microcontroller
- Raspberry Pi
- KY-026 branddetectiemodule
- KY-006 passieve buzzermodule
- MQTT broker (bijv. Mosquitto)
- Grafana

## Architectuur

Het systeem bestaat uit de volgende componenten:

- **ESP32:** Verantwoordelijk voor het detecteren van brand.
- **Raspberry Pi:** Zorgt voor de werking van de buzzer en fungeert als MQTT broker en zorgt voor de visuele monitoring via Grafana.
- **KY-026 Branddetectiemodule:** Detecteert de aanwezigheid van brand.
- **KY-006 Passieve Buzzermodule:** Activeert het alarm bij branddetectie.
- **MQTT-protocol:** Zorgt voor de communicatie tussen de ESP32 en de Raspberry Pi.
- **Grafana:** Biedt een visuele interface om de status en meldingen van het systeem te monitoren.

## Elektrische Schema's

Voor het aansluiten van de componenten kun je de volgende elektrische schema's raadplegen:
### ESP32 met KY-026 (branddetectiemodule) en LED
![Elektrisch Schema ESP32 met KY-026 Branddetectiemodule en LED](https://github.com/VHJonas/Brandalarm/blob/main/ESP32.jpg)

### Raspberry Pi met KY-006 (passieve buzzermodule) en knop
![Elektrisch Schema Raspberry Pi en KY-006 Passieve Buzzermodule](https://github.com/VHJonas/Brandalarm/blob/main/Raspi.jpg)

## C++ Codes

De volgende C++ codes zijn beschikbaar voor dit project:
- [Volledige C++ Code](https://github.com/VHJonas/Brandalarm/blob/main/full_code.ino)
- [C++ Code om de Branddetectiemodule te Testen](https://github.com/VHJonas/Brandalarm/blob/main/Check_fire_LED.ino)

## Python Code

De volgende python code voor dit project:
- [Volledige Python Code](............)

## Documentatie

Meer gedetailleerde informatie over het project is te vinden in de volgende documentatie:
- [Project Uitleg (PDF)](https://github.com/VHJonas/Brandalarm/blob/main/Herkansing%20Embedded%20Microcontroller%20Applications.pdf)

## Installatie

1. **ESP32 Configuratie:**
   - Download en installeer de Arduino IDE.
   - Voeg de ESP32 board manager URL toe in de Arduino IDE instellingen.
   - Installeer de benodigde bibliotheken voor MQTT.
   - Upload de ESP32 code naar de microcontroller.

2. **Raspberry Pi Configuratie:**
   - Installeer een MQTT broker zoals Mosquitto.
   - Installeer Grafana en configureer de benodigde dashboards.
   - Zorg ervoor dat de Raspberry Pi correct geconfigureerd is om met de ESP32 te communiceren via MQTT.

## Gebruik

1. Sluit de KY-026 branddetectiemodule aan op de ESP32.
2. Sluit de KY-006 passieve buzzermodule aan op de ESP32.
3. Start de ESP32 en de Raspberry Pi.
4. Open Grafana om de status en meldingen van het systeem te monitoren.

## Contributie

Contributies zijn welkom! Voel je vrij om pull requests in te dienen of issues aan te maken voor suggesties en verbeteringen.

## Licentie

Dit project is gelicentieerd onder de MIT Licentie - zie het [LICENSE](LICENSE) bestand voor details.
