/**
 * @file logga.h
 * @brief this file implements a minimalistic logging interface
 * for embedded or desktop apps
 * @author Edwin Mwiti
 */

#ifndef LOGGA_H
#define LOGGA_H

#include <stdio.h> // todo: add check for embedded
#include <stdint.h>
#include <stdlib.h>

typedef struct Logga* Logga_Type_t; /* forward declare Logga structure */
typedef struct SystemTime* SystemTime_t; /* to hold the current system time -> will be passed in by the user*/

/**
 * Functions
 */

/**
 * @brief to be used only for desktop applications where dynamic allocation is not a
 * big memory issue
 * @return
 */
Logga_Type_t logga_create();

/**
 * @brief init_logga initialize a logging object
 * @param _logga_inst instance of the logger object being used
 * @param fname filename to log to
 * @param f_size size of the file to create
 */
 void init_logga(Logga_Type_t _logga_inst, const char* fname, uint32_t f_size);

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
  * @param dir_name
  */
 void check_num_files(Logga_Type_t _logga_inst, const char* dir_name);

 /**
  * @brief writes the log to filename passed during creation
  * @param t_stamp
  * @param TAG
  * @param LEVEL
  * @param MSG
  */
 void write_log(Logga_Type_t _logga_inst, unsigned long t_stamp, const char* TAG, const char* LEVEL, const char* MSG);


#endif