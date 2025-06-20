#include <iostream>
#include <stdint.h> /* for fixed integer sizes */
#include "../../logga.h"
#include <string.h>

//#define NLOG

#ifndef NLOG
    /* create logger object */
    Logga_Type_t system_logger = create_logga();
    #define LOG_FILE_SIZE
#endif

int main() {

    /* initialize logger with desired file parameters */
    const char* filename = "/log-file.log";

#ifndef NLOG
    init_logga(system_logger, filename );

#endif

    //std::cout <<"dragon moto testing 1..2" << '\n';

    return 0;
}