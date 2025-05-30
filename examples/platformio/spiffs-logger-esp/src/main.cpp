#include <Arduino.h>
#include "logga.h"

const char* file = "logger.log";
uint32_t FILE_SIZE_1MB = 1048576; // 1 MB

void setup() {
    Serial.begin(115200);
    int logger_status = create_logga(file, FILE_SIZE_1MB);

    Serial.println(logger_status);
}

void loop() {

}