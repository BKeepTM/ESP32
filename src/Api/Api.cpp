#include "Api.h"

Api::Api(std::string apiUrl) : mqttClient(espClient) {
    this->apiUrl = apiUrl;
}

// WiFi povezava
void Api::connect() {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("Timer set to 5 seconds before first reading.");
}

String Api::printLocalTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        return String("Failed to obtain time");
    }
    char timeStringBuff[25]; 
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(timeStringBuff);
}

// MQTT povezava (HiveMQ Cloud TLS)
void Api::connectMQTT() {
    espClient.setInsecure(); 
    mqttClient.setServer(mqttServer, mqttPort);

    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        if (mqttClient.connect("esp32-hive-5", mqttUser, mqttPassword)) {
            Serial.println(" connected");
        } else {
            Serial.print(" failed, rc=");
            Serial.println(mqttClient.state());
            delay(2000);
        }
    }
}

// MQTT loop
void Api::loop() {
    mqttClient.loop();
}

bool Api::postWeight(float weight) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected");
        return false;
    }

    if (!mqttClient.connected()) {
        connectMQTT();
    }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    String payload = "{";
    payload += "\"weight\":" + String(weight, 2) + ",";
    payload += "\"hiveId\":5,";
    payload += "\"time\":\"" + printLocalTime() + "\"";
    payload += "}";

    Serial.println("Publishing weight via MQTT:");
    Serial.println(payload);

    bool ok = mqttClient.publish(weightTopic, payload.c_str(), false);

    if (ok) {
        Serial.println("MQTT weight sent");
    } else {
        Serial.println("MQTT publish failed");
    }

    mqttClient.loop(); 

    return ok;
}


bool Api::postSystemNote(float weight) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected");
        return false;
    }

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    if (!http.begin(client, "https://pi.darkosever.si/notes")) {
        Serial.println("Napaka pri http.begin() - notes");
        return false;
    }

    http.setTimeout(5000);
    http.addHeader("Content-Type", "application/json");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    String time = printLocalTime();

    String body = "{";
    body += "\"hiveId\":5,";
    body += "\"time\":\"" + time + "\",";
    body += "\"content\":\"EXTREME EVENT: Hive weight measured 0.00 kg\"";
    body += "}";

    Serial.println("Posting EXTREME SYSTEM NOTE:");
    Serial.println(body);

    int responseCode = http.POST(body);
    Serial.print("HTTP Response code: ");
    Serial.println(responseCode);

    http.end();
    delay(2000);

    return responseCode > 0;
}
