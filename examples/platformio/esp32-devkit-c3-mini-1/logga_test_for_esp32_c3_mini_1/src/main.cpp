#include <Arduino.h>
#include "logga.h"

const char* my_log_file = "/test1.log";

Logga system_log(my_log_file, "/");

void setup() {
  Serial.begin(115200);

  FILE_CREATE_STATUS status = system_log.logga_init();

  Serial.println(status);

  delay(1000);

  /* test file dump */
  system_log.logga_dump(my_log_file);
}

void loop() {
  
}
