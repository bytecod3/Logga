#include <Arduino.h>

#define ESP32_ARDUINO // must be defined to use ESP32  Arduino framework

#include "../../../../logga.h"


/* define the filename */
const char* log_file_name = "log1.log";

/* define file  size you want to create */
uint32_t FILE_1MB = 1048576;

void setup() {
	Serial.begin(115200);
	delay(200);

	// create file
	/* create logga instance */
	Logga_Type_t logger = c_log();
	
	//if(log_status) {
		//Serial.println("Logga created ok!");
	//} else {
		//Serial.println("Failed to create Logga. Please check SPIFFS partition.");
	//}

}

void loop() {

}