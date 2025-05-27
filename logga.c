/**
 *
 * @file logga.c
 * @brief implements logga.h
 * @author Edwin Mwiti
 *
 */

#include "logga.h"

//typedef struct SystemTime{
//    day,
//    yr,
//    month,
//    hr,
//    min,
//    sec,
//    msec,
//};

static const char* ntp_server = "pool.ntp.org";
static unsigned long epoch_time;

typedef struct Logga {
    const char* _fname;
    uint32_t _sz;
    // const char* _f_system // todo: handle different file systems
} Logga_t;

Logga_Type_t c_log() {
    return (Logga_Type_t) malloc(sizeof(Logga_t));
}

/**
 *
 * @brief to be used only for desktop applications where dynamic allocation is not a
 * big memory issue
 * @return
 *
 */
uint8_t create_logga(const char* fname, uint32_t f_size) {
    Logga_Type_t ob = malloc(sizeof(Logga_t));

    if(ob != NULL) {
        ob->_fname = f_name;
        ob->_sz = f_size;
        if(init_logga(ob, ob->_fname, ob->_sz)) {
            return 0xff;
        }
    } else {
        return 0x00;
    }
}

uint8_t init_logga(Logga_Type_t _logga_inst, const char* fname, uint32_t f_size) {
    #if USE_EMBEDDED
        // todo:check for MCU target being used -> for now use esp32
        if(init_SPIFFS(_logga_inst)){
            return 0xff;
        } else {
            return 0x00;
        }
    #else
        /* create a file with this size */
        FILE* fp = fopen(obj->_fname, "a");
        fprintf(fp, "----log File----");
        fclose(fp);
    #endif
}

uint8_t init_SPIFFS(Logga_Type_t _logga_inst) {
    if(SPIFFS.begin(true)) {
        File log_file = SPIFFS.open(_logga_inst->_fname, "a");
        if (log_file) {
            log_file.print("----log file----");
            log_file.close()
            return 0xff;
        } else {
            return 0x00;
        }
    } else {
        return 0x00;
    }

}

const char* get_ntp_time(Logga_Type_t obj){
#if NTP_ENABLE
    // check if wi-fi connected
    // you can call this function after making sure wi-fi is connected
    if(WiFi.status() != WIFI_CONNECTED) {
        Serial.println("Wifi not available. Please connect wifi");
        return;
    } else {
        const char* ntp_server = "pool.ntp.org";
        const long gmt_offset_sec = 0;
        const int daylight_saving_sec = 0;

        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)) {
          Serial.println("Failed to obtain time");
          return;
        }

        char time_buffer[128];
        memset(time_buffer, 0, 128);

        sprintf(time_buffer,
                "%A, %B %d %Y %H:%M:%S",
                &timeinfo->tm_wday,
                &timeinfo->tm_mon,
                &timeinfo->tm_mday,
                &timeinfo->tm_year,
                &timeinfo->tm_hour,
                &timeinfo->tm_min,
                &timeinfo->tm_sec,
                );

        return time_buffer;
    }
#else
    // mainstream C -> get CPU time

#endif
}

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

void log_trace(Logga_Type_t obj,const char* tag, const char* msg) {
    const char* lvl = "TRACE";
    unsigned char tstamp = get_ntp_time(obj);

    write_log(obj, tstamp, tag, lvl, msg);
}

#ifdef __cplusplus
#endif