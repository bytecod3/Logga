#include <Arduino.h>
#include "logga.h"

const char* filename = "/logger.log";
uint32_t FILE_SIZE_1MB = 1048576; // 1 MB

void setup() {
    Serial.begin(115200);
    Logga_Type_t logger = create_logga();

    if(logger != NULL) {
        Serial.println("Logger created OK!");
        uint8_t logger_status = init_logga(logger,filename,FILE_SIZE_1MB);
        Serial.printf("return value: %d\n", logger_status);
    } else {
        Serial.println("Logger initialization failed");
    }
    

}

void loop() {

}