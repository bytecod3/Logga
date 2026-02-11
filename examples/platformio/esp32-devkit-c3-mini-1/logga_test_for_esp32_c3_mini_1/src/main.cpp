#include <Arduino.h>
#include "logga.h"

Logga system_log("/test1.log", "/");

void setup() {
  Serial.begin(115200);

  FILE_CREATE_STATUS status = system_log.logga_init();

  Serial.println(status);

  
}

void loop() {
  
}
