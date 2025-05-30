/**
 * @file logga.h
 * @brief this file implements a minimalistic logging interface
 * for embedded or desktop apps
 * @author Edwin Mwiti
 */



#ifndef LOGGA_H
#define LOGGA_H

#include "config.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Logga* Logga_Type_t;         /* forward declare Logga structure */
typedef struct SystemTime* SystemTime_t;    /* to hold the current system time -> will be passed in by the user*/

/**
 * Functions
 */

/**
 * @brief allocate teh object we are going to be using for logging
 * @return
 * 
 */
Logga_Type_t create_logga();

/**
 * @brief init_logga initialize a logging object
 * @param _logga_inst instance of the logger object being used
 * @param fname filename to log to
 * @param f_size size of the file to create
 */
uint8_t init_logga(Logga_Type_t _logga_inst, const char* fname, uint32_t f_size);
const char* get_ntp_time(Logga_Type_t obj);

/**
 * @brief Initialize SPIFFS file system for ESP32
 * @param _logga_inst
 * @return 1 if successful
 */
uint8_t init_SPIFFS(Logga_Type_t _logga_inst);

 /**
  * @brief check the size of file to create
  * if the size is greater than the allowed file size, return the default max allowed file size
  * @param sz size passed by the caller
  */
 uint32_t check_file_size(Logga_Type_t _logga_inst,  uint32_t sz);

 /**
  * @brief check the number of files already created in the passed directory
  * If the number of files is greater than the allowed number of files,
  * delete the oldest file to create space -> majorly for embedded
  * todo: add embedded usage check
  * @param dir_name directory to check
  */
 void check_num_files(Logga_Type_t _logga_inst, const char* dir_name);

 /**
  * @brief writes the log to filename passed during creation
  * @param t_stamp
  * @param TAG
  * @param LEVEL
  * @param MSG
  */
 void write_log(Logga_Type_t _logga_inst, const char* t_stamp, const char* TAG, const char* LEVEL, const char* MSG);

 /**
  * @brief log data to the given file
  * This function is for use in embedded controller
  * @param _logga_inst
  * @param t_stamp
  * @param TAG
  * @param LEVEL
  * @param MSG
  */
  void log_message(Logga_Type_t _logga_inst, unsigned long t_stamp, const char* TAG, const char* LEVEL, const char* MSG);
void log_trace(Logga_Type_t obj, const char* tag, const char* msg);
void log_debug(const char* tag, const char* msg);
void log_info(const char* tag, const char* msg);
void log_warn(const char* tag, const char* msg);
void log_error(const char* tag, const char* msg);
void log_fatal(const char* tag, const char* msg);

#ifdef __cplusplus
}
#endif

#endif

