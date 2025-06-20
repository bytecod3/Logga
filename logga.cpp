/**
 * @file logga.cpp
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
    #include <windows.h>
    #include <stdio.h>
    #include <string.h>
    #include <tchar.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <stdbool.h>

#elif defined(linux)
    #include <unistd.h> /* todo: fixme */

//#elif check for linux
#else

    #warning "No valid platfrom defined."

#endif

static const char* ntp_server = "pool.ntp.org";
static unsigned long epoch_time;

typedef struct Logga {
    char filepath[50];
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

uint8_t init_logga(Logga_Type_t _logga_inst, const char* fname) {

    strcpy(_logga_inst->filepath, "log"); /* default folder to separate log files from other files */
    _logga_inst->_fname = fname;

#ifdef ESP32_ARDUINO
    // todo:check for MCU target being used -> for now use esp32
    if(init_SPIFFS(_logga_inst)){
        return 0xff;
    } else {
        return 0x00;
    }

#else
    /* separate the log files into a new folder */
        DIR* dir = opendir(_logga_inst->filepath);

        if (dir != NULL) {
            printf("Dir %s exists \r\n", _logga_inst->filepath);
            char path[50];
            strcpy(path, _logga_inst->filepath);
            strcat(path, _logga_inst->_fname);

            printf("%s\n", path);
            FILE* fp = fopen(path, "w"); /* create file */

            if(fp != NULL) {
                printf("File exists\n ");
                fclose(fp);
                //return FILE_CREATE_STATUS::FILE_EXISTS; // returns 2

            } else {
                /* file does not exist create a file with this size */
                /* TODO: check allowed file size */

                printf("File does not exist. creating file \n");

                fp = fopen(path, "w");

                /* confirm creation */
                if(fp != NULL) {
                    printf("File created success");

                    fclose(fp);
                } else {
                    printf("Failed to create file");
                }

//                strcat(_logga_inst->filepath, _logga_inst->_fname);
//                FILE* f_ptr = fopen(_logga_inst->filepath, "a");
//                #if defined(_WIN32)
//                    fseek(f_ptr, MAX_FILE_SIZE, SEEK_SET);
//                    fputs((const char *)'\0', f_ptr);
//                    fseek(f_ptr, 0, SEEK_SET);
//                #elif defined(linux)
//                    ftruncate(f_ptr, f_size);
//                #endif
//
//                fprintf(f_ptr, "----log File----\r\n");
//                fclose(f_ptr);

            }

            closedir(dir);
            return FILE_CREATE_STATUS::FILE_CREATE_OK;

        } else {
            printf("filepath: %s\n", _logga_inst->filepath);
            mkdir(_logga_inst->filepath);
            //printf("Dir does not exist. Created dir: %s \n");
            return FILE_CREATE_STATUS::FOLDER_CREATE_OK;
        }

        return 0x00; /* should not be called */

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
#endif

#ifdef ESP32_ARDUINO
    void list_dir(fs::FS &fs, const char* dirname, uint8_t levels) {


            Serial.println("Listing directory: %s\r\n", dirname);
            File root = fs.open(dirname);

            if(!root) {
                Serial.println(" - Failed to open directory");
                return;
            }

            if (!root.isDirectory()) {
                Serial.println(" - not a directory");
                return;
            }

            File file = root.openNextFile();
            while(file) {
                if(file.isDirectory()) {
                    Serialprint("   DIR:    ");
                    Serial.println(file.name());
                    if(levels) {
                        listDir(fs, file.name(), levels - 1);
                    }

                } else {
                    Serial.print("  FILE:   ");
                    Serial.print(file.name());
                    Serial.print("      SIZE:   ");
                    Serial.println(file.size());
                }

                file = root.openNextFile();
            }


    }
#endif

void logga_list_dir(Logga_Type_t _logga_inst) {
    if(_logga_inst == NULL){
        return;
    }else {
#ifdef ESP32_ARDUINO
        _logga_inst->list_dir(SPIFFS, "/", 1);
#endif
    }
}


void check_num_files(Logga_Type_t _logga_inst, const char* dir_name) {
#ifdef ESP32_ARDUINO

#endif
}

#ifdef ESP32_ARDUINO
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
#endif // ESP32_ARDUINO

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

