#pragma once
#include <string>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include "time.h"

class Api {
private:
    std::string apiUrl;

    // WiFi
    const char* ssid = "A1-0EE5E0"; 
    const char* password = "8UUNQN8P8G"; 
    const char* ntpServer = "pool.ntp.org";
    const long  gmtOffset_sec = 3600;
    const int   daylightOffset_sec = 3600;

    // MQTT
    const char* mqttServer = "c658728d56404b908ec770ff56fc9a76.s1.eu.hivemq.cloud";
    const int mqttPort = 8883;
    const char* mqttUser = "bkeep";
    const char* mqttPassword = "Hrustanec12";
    const char* weightTopic = "hives/upload";

    WiFiClientSecure espClient;
    PubSubClient mqttClient;

    void connectMQTT();

public: 
    Api(std::string apiUrl);

    void connect();
    void loop(); // klic v main loop za MQTT
    bool postWeight(float weight);       // MQTT
    bool postSystemNote(float weight);   // HTTP
    String printLocalTime();
};
