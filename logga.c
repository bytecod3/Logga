/**
 * @file logga.c
 * @brief implements logga.h
 * @author Edwin Mwiti
 */

#include "logga.h"

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

