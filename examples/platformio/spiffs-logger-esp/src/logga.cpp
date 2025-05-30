/**
 *
 * @file logga.c
 * @brief implements logga.h
 * @author Edwin Mwiti
 *
 */

#include "logga.h"

#ifdef ESP32_ARDUINO
    
    #include <Arduino.h>
    #include <WiFi.h>
    #include <SPIFFS.h>
    #include <time.h>
    #include <FS.h>
    
#elif defined(_WIN32)
    // check desktop
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>

#elif defined(linux)
    #include <unistd.h>
    
//#elif check for linux
#else 
    #warning "No valid platfrom defined."
#endif

static const char* ntp_server = "pool.ntp.org";
static unsigned long epoch_time;

typedef struct Logga {
    const char* _fname;
    uint32_t _sz;
    #if defined(ESP32_ARDUINO)
        char* tstamp;
    #endif
} Logga_t;

/**
 *
 * @brief to be used only for desktop applications where dynamic allocation is not a
 * big memory issue
 * @return
 *
 */
Logga_Type_t create_logga() {
    Logga_Type_t ob = (Logga_Type_t) malloc(sizeof(Logga_t));
    if(ob != NULL) {
        return ob;
    } 
    return NULL;
}

uint8_t init_logga(Logga_Type_t _logga_inst, const char* fname, uint32_t f_size) {
    _logga_inst->_fname = fname;
    _logga_inst->_sz = f_size;

    #ifdef ESP32_ARDUINO
        // todo:check for MCU target being used -> for now use esp32
        if(init_SPIFFS(_logga_inst)){
            return 0xff;
        } else {
            return 0x00;
        }
    #else // desktop C
        /* create a file with this size */
        FILE* fp = fopen(_logga_inst->_fname, "a");
        #if defined(_WIN32)
            fseek(fp, f_size, SEEK_SET);
            fputs('\0', fp);
            fseek(fp, 0);
        #elif defined(linux)  
            ftruncate(fp, f_size);
        #endif
        
        fprintf(fp, "----log File----");
        fclose(fp);
    #endif
}

#ifdef ESP32_ARDUINO
uint8_t init_SPIFFS(Logga_Type_t _logga_inst) {
    if(SPIFFS.begin(true)) {
        File log_file = SPIFFS.open(_logga_inst->_fname, "a");
        if (log_file) {
            log_file.print("----log file----");
            log_file.close();
            return 0xff;
        } else {
            return 0x00;
        }
    } else {
        return 0x00;
    }

}

const char* get_ntp_time(Logga_Type_t _inst){

    // check if wi-fi connected
    // you can call this function after making sure wi-fi is connected
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi not available. Please connect wifi");
        return "Wifi unavailable";
    } else {
        const char* ntp_server = "pool.ntp.org";
        const long gmt_offset_sec = 0;
        const int daylight_saving_sec = 0;

        struct tm timeinfo;
        struct tm* p_timeinfo = &timeinfo;
        if(!getLocalTime(&timeinfo)) {
          Serial.println("Failed to obtain time");
          return "Could not get time"; // todo: USE AN ERROR CONST
        }

        static char time_buffer[128];
        //memset(time_buffer, 0, 128);

        sprintf(time_buffer,
                "%A, %B %d %Y %H:%M:%S",
                &p_timeinfo->tm_wday,
                &p_timeinfo->tm_mon,
                &p_timeinfo->tm_mday,
                &p_timeinfo->tm_year,
                &p_timeinfo->tm_hour,
                &p_timeinfo->tm_min,
                &p_timeinfo->tm_sec
                );

        return time_buffer;
    }
}
#endif // end of ESP32 SPIFFS

void write_log(Logga_Type_t obj, const char* t_stamp, const char* TAG, const char* LEVEL, const char* MSG) {
    FILE* fp = fopen(obj->_fname, "a");

    /* create message */
    char msg_buf[256];
    sprintf(msg_buf,
            "%s %s\t %s\t %s\n",
            t_stamp, TAG, LEVEL, MSG
            );

    fprintf(fp, msg_buf);
    fclose(fp);
}

void log_trace(Logga_Type_t obj, const char* tag, const char* msg) {
    const char* lvl = "TRACE";

    #ifdef ESP32_ARDUINO
        const char* tstamp = get_ntp_time(obj);
    #else
        const char tstamp[] = "00:00:00";
    #endif

    write_log(obj, tstamp, tag, lvl, msg);
}

