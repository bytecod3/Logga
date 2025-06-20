#include <iostream>
#include <stdint.h> /* for fixed integer sizes */
#include "../../logga.h"
#include <string.h>

#define NLOG

#ifndef NLOG
    /* create logger object */
    Logga_Type_t system_logger = create_logga();
    #define LOG_FILE_SIZE
#endif

int main() {

    /* initialize logger with desired file parameters */
    char filepath[50] = "/logger";
    const char* filename = "/log1.log";

    strcat(filepath, filename);
    printf("filepath: %s\n", filepath);


#ifndef NLOG
    init_logga(system_logger, filename, )
#endif

    std::cout <<"dragon moto testing" << '\n';

    return 0;
}