/**
 * @file logga.cpp
 * @brief implements logga.h
 * @author Edwin M.
 *
 */

#include "logga.h"

#ifdef ESP32_ARDUINO
    #include <Arduino.h>
    #include <WiFi.h>
    #include <SPIFFS.h>
    #include <time.h>
    #include <FS.h>

// todo: check for other architectures
#else
    #warning "No valid platfrom defined."
#endif

/**
 * @brief The filename must begin with "/". for example "/file1.log"
 */
Logga::Logga( const char* f_name, const char* dir_name="/") {

    #if ESP32_ARDUINO

        this->_ntp_server = "ntp.pool.org";
        if(f_name != NULL && dir_name != NULL) {
            this->_f_name = f_name;
            this->_dir_name = dir_name;
        }
        
     #endif
}

FILE_STATUS Logga::logga_init() {
    #if ESP32_ARDUINO
        /* use SPIFFS to store file */
        /* todo: check for file system */
        if(SPIFFS.begin(true)) {
            File f = SPIFFS.open(this->_f_name, "a");

            if (f) {
                /* prepare file header */
                char _f_header[30];
                //this->_get_time();
                sprintf(_f_header, "---Log File---\r\n");
                f.print(_f_header);
                f.close();

                return LOGGA_FILE_CREATE_OK;
            } else {
                return LOGGA_FAILED_TO_CREATE_LOG_FILE;
            }

        } else {
            return LOGGA_FAILED_TO_OPEN_SPIFFS;
        }

    #endif
}

FILE_STATUS Logga::logga_dump(const char* f_name) {
    #if ESP32_ARDUINO

        if(f_name != NULL) {
            File f = SPIFFS.open(f_name);
            if(!f || f.isDirectory()) {
                return LOGGA_FAILED_TO_OPEN_FILE;
            } else {
                while(f.available()) {
                    Serial.write(f.read());
                }
            }

             f.close();

             return LOGGA_FILE_DUMP_OK;


        } else {
            return LOGGA_INVALID_FILENAME;
        }

    #endif
}

FILE_STATUS Logga::logga_delete(const char* f_name) {
    #if ESP32_ARDUINO
        if(f_name != NULL) {
            if(SPIFFS.remove(f_name)){
                return LOGGA_FILE_DELETE_OK;
            } else {
                return LOGGA_FAILED_TO_DELETE_FILE;
            }

        } else {
            return LOGGA_INVALID_FILENAME;
        }
    #endif
}

void Logga::_get_time(void) {
    #if ESP32_ARDUINO
        /* get ntp_time */
        
    #endif
}

FILE_STATUS Logga::logga_clear_file(const char* f_name) {
    #if ESP32_ARDUINO
        if(f_name != NULL) {
            File f = SPIFFS.open(f_name, "w");
            if(!f || f.isDirectory()) {
                return LOGGA_FAILED_TO_OPEN_FILE;
            } else {
                /* opening a file in write mode automatically clears the file contents if the file exists */
                
                f.write('\0');
                f.close();
                return LOGGA_FILE_CLEARED_OK;
            }
        } else {
            return LOGGA_INVALID_FILENAME;
        }
    #endif
}

// /* represents a logging object */
// typedef struct Logga {
//     char filepath[20];
//     const char* _fname;
//     uint32_t _sz;

//     #if defined(ESP32_ARDUINO)
//         char* tstamp;
//     #endif
// } Logga_t;

// /**
// * @brief initializes the logga object depending on the chosen architecture
// */
// uint8_t init_logga(Logga_Type_t _logga_inst, const char* fname) {
//     strcpy(_logga_inst->filepath, "logs");         /* default folder to separate log files from other files */
//     _logga_inst->_fname = fname;

//     #ifdef ESP32_ARDUINO
//         if(init_SPIFFS(_logga_inst)){
//             return 1;
//         } else {
//             return 0;
//         }
//     #endif
// }

// #ifdef ESP32_ARDUINO
// uint8_t init_SPIFFS(Logga_Type_t _logga_inst) {
//     if(SPIFFS.begin(true)) {
//         File log_file = SPIFFS.open(_logga_inst->_fname, "a");
//         if (log_file) {
//             log_file.print("----log file----");
//             log_file.close();
//             return LOGGA_FILE_CREATE_OK;
//         } else {
//             return LOGGA_FAILED_TO_CREATE_LOG_FILE;
//         }
//     } else {
//         return LOGGA_SPIFFS_FAILED_TO_OPEN;
//     }

// }
// #endif

// #ifdef ESP32_ARDUINO
//     void list_dir(fs::FS &fs, const char* dirname, uint8_t levels) {
//             #if DEBUG
//                 Serial.printf("Listing directory: %s\r\n", dirname);
//             #endif
//             File root = fs.open(dirname);

//             if(!root) {
//                 #if DEBUG
//                     Serial.println(" - Failed to open directory");
//                 #endif
//                 return;
//             }

//             if (!root.isDirectory()) {
//                 #if DEBUG
//                     Serial.println(" - not a directory");
//                 #endif
//                 return;
//             }

//             File file = root.openNextFile();
//             while(file) {
//                 if(file.isDirectory()) {
//                     #if DEBUG
//                         Serial.print("   DIR:    ");
//                         Serial.println(file.name());
//                     #endif
            
//                     if(levels) {
//                         list_dir(fs, file.name(), levels - 1);
//                     }

//                 } else {
//                     #if DEBUG
//                         Serial.print("  FILE:   ");
//                         Serial.print(file.name());
//                         Serial.print("      SIZE:   ");
//                         Serial.println(file.size());
//                     #endif
//                 }

//                 file = root.openNextFile();
//             }
//     }
// #endif

// /**
// */

// void logga_list_dir(Logga_Type_t _logga_inst) {
//     if(_logga_inst == NULL){
//         return;

//     }else {
// #ifdef ESP32_ARDUINO
//         _logga_inst->list_dir(SPIFFS, "/", 1);
// #endif
//     }
// }

// void check_num_files(Logga_Type_t _logga_inst, const char* dir_name) {
// #ifdef ESP32_ARDUINO

// #endif
// }

// #ifdef ESP32_ARDUINO
// const char* get_ntp_time(Logga_Type_t _inst){

//     // check if wi-fi connected
//     // you can call this function after making sure wi-fi is connected
//     if(WiFi.status() != WL_CONNECTED) {
//         Serial.println("Wifi not available. Please connect wifi");
//         return "Wifi unavailable";
//     } else {
//         const char* ntp_server = "pool.ntp.org";
//         const long gmt_offset_sec = 0;
//         const int daylight_saving_sec = 0;

//         struct tm timeinfo;
//         struct tm* p_timeinfo = &timeinfo;
//         if(!getLocalTime(&timeinfo)) {
//             Serial.println("Failed to obtain time");
//             return "Could not get time"; // todo: USE AN ERROR CONST
//         }

//         static char time_buffer[128];
//         //memset(time_buffer, 0, 128);

//         sprintf(time_buffer,
//                 "%A, %B %d %Y %H:%M:%S",
//                 &p_timeinfo->tm_wday,
//                 &p_timeinfo->tm_mon,
//                 &p_timeinfo->tm_mday,
//                 &p_timeinfo->tm_year,
//                 &p_timeinfo->tm_hour,
//                 &p_timeinfo->tm_min,
//                 &p_timeinfo->tm_sec
//         );

//         return time_buffer;
//     }
// }
// #endif // ESP32_ARDUINO

// void write_log(Logga_Type_t _logga_inst, const char* t_stamp, const char* TAG, const char* LEVEL, const char* MSG) {
//     FILE* fp = fopen(_logga_inst->_fname, "a");

//     /* create message */
//     char msg_buf[256];
//     sprintf(msg_buf,
//             "%s %s\t %s\t %s\n",
//             t_stamp, TAG, LEVEL, MSG
//     );

//     fprintf(fp, msg_buf);
//     fclose(fp);
// }

// void log_trace(Logga_Type_t obj, const char* tag, const char* msg) {
//     const char* lvl = "TRACE";

// #ifdef ESP32_ARDUINO
//     const char* tstamp = get_ntp_time(obj);
// #else
//     const char tstamp[] = "00:00:00";
// #endif

//     write_log(obj, tstamp, tag, lvl, msg);
// }

