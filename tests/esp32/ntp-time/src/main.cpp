#include <Arduino.h>
#include <WiFi.h>
#include <time.h>


const char* ntp_server = "pool.ntp.org";
const long gmt_offset = 0;
const int daylight_saving = 3600;


void printLocalTime() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//    Serial.print("Day of week: ");
//    Serial.println(&timeinfo, "%A");
//    Serial.print("Month: ");
//    Serial.println(&timeinfo, "%B");
//    Serial.print("Day of Month: ");
//    Serial.println(&timeinfo, "%d");
//    Serial.print("Year: ");
//    Serial.println(&timeinfo, "%Y");
//    Serial.print("Hour: ");
//    Serial.println(&timeinfo, "%H");
//    Serial.print("Hour (12 hour format): ");
//    Serial.println(&timeinfo, "%I");
//    Serial.print("Minute: ");
//    Serial.println(&timeinfo, "%M");
//    Serial.print("Second: ");
//    Serial.println(&timeinfo, "%S");
}

void setup()  {
    Serial.begin(115200);
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    configTime(gmt_offset,  daylight_saving, ntp_server);
    printLocalTime();
}

void loop() {
    printLocalTime();
}
