/**
 * @file logga.c
 * @brief implements logga.h
 * @author Edwin Mwiti
 */

#include "logga.h"

typedef struct SystemTime{
    day,
    yr,
    month,
    hr,
    min,
    sec,
    msec,
};

static const char* ntp_server = "pool.ntp.org";
static unsigned long epoch_time;

typedef struct Logga {
    const char* _fname;
    uint32_t _sz;
    // const char* _f_system // todo: handle different file systems
} Logga_t;

/**
 * @brief to be used only for desktop applications where dynamic allocation is not a
 * big memory issue
 * @return
 */
Logga_Type_t logga_create() {
    return (Logga_Type_t) malloc(sizeof(Logga_t));
}

void init_logga(Logga_Type_t obj, const char* f_name, uint32_t f_size) {
    obj->_fname = f_name;
    obj->_sz = f_size;

    /* create a file with this size */
    FILE* fp =  fopen(obj->_fname, "a");
    fprintf(fp, "----Log File----");
    fclose(fp);
}

unsigned long get_ntp_time(Logga_Type_t obj){
#if NTP_ENABLE
    // check if wifi connected
    // you can call this function after making sure wifi is connected
    if(WiFi.status() != WIFI_CONNECTED) {
        Serial.println("Wifi not available. Please connect wifi");
        return;
    }
#else
#endif
}


void write_log(Logga_Type_t obj, unsigned long t_stamp, const char* TAG, const char* LEVEL, const char* MSG) {
    FILE* fp = fopen(obj->_fname, "a");

    /* create message */
    char msg_buf[256];
    sprintf(msg_buf,
            "%lu %s\t %s\t %s\n",
            t_stamp, TAG, LEVEL, MSG
            );

    fprintf(fp, msg_buf);
    fclose(fp);
}

void log_trace(Logga_Type_t obj,const char* tag, const char* msg) {
    const char* lvl = "TRACE";
    write_log(obj, , tag, lvl, msg);
}
