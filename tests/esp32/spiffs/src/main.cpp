#include <Arduino.h>
#include <time.h>

void get_time()  {
    time_t now;
    char strftime_buf[64];

    struct tm timeinfo;
    time(&now);
    // set time to East African Standard time
    setenv("TZ", "GMT+3", 1);

    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf),"%c", &timeinfo);
    Serial.printf("Current time is : %s\n", strftime_buf);
}

void setup() {
    Serial.begin(115200);
    get_time();
}

void loop() {

}