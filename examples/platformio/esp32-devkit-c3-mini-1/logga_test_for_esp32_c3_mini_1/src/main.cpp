#include <Arduino.h>
#include "logga.h"

const char* my_log_file = "/test1.log";

Logga system_log(my_log_file, "/");

void setup() {
  Serial.begin(115200);

  FILE_STATUS status = system_log.logga_init();

  Serial.println(status);

  delay(1000);

  Serial.println("Beginning test: ESP32-C3-MINI-1");

  /* test file dump */
  Serial.println("[]Dumping file...");
  system_log.logga_dump(my_log_file);

  /* test clearing file */
  Serial.println("[]Clearing file...");
  system_log.logga_clear_file(my_log_file);

  /* redump the file to confirm */
  Serial.println("[]Redumping file...");
  system_log.logga_dump(my_log_file);

  Serial.println("End of setup test");
}

void loop() {
  
}
