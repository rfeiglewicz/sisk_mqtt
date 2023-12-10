#include <Arduino.h>
#include <PicoMQTT.h>
#include <ESP8266WiFi.h>

PicoMQTT::Server mqtt;

char ssid[] = "sisk_gr_1";      // your network SSID (name)
char pass[] = "sisk1234"; // your network password

void setup() {
    // Usual setup
    Serial.begin(115200);
    WiFi.softAP(ssid, pass);
    Serial.println("AP started");
    Serial.println("IP address: " + WiFi.softAPIP().toString());

    // Subscribe to a topic pattern and attach a callback
    mqtt.subscribe("#", [](const char * topic, const char * payload) {
        Serial.printf("Received message in topic '%s': %s\n", topic, payload);
    });

    // Start the broker
    mqtt.begin();
}

void loop() {
    // This will automatically handle client connections.  By default, all clients are accepted.
    mqtt.loop();

    if (random(1000) == 0)
        mqtt.publish("picomqtt/welcome", "Hello from PicoMQTT!");
}