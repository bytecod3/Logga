#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "logga.h"


#define F_SIZE_2MB 2097192

int main() {

    /* create logga instance */
    Logga_Type_t system_logger = logga_create();

    /* initialize logga */
    char* log_file_name = "log1.log";
    init_logga(system_logger, log_file_name, F_SIZE_2MB);

    /* create logging tags */
    const char* TAG = "DB";

    char c;
    while(1) {

        // get cpu time
        clock_t tstamp = clock();

        write_log(system_logger, tstamp , TAG, "INFO", "test message 1");

        if(kbhit()) {
            c = getch();
            if(c == 'k') { // stop logging
                puts("Keyboard interrupt");
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}