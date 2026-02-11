/*
* @author: Edwin M.
*/

#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 1

#define EMBEDDED_ENABLE           (1)        /* set to 0 when using on desktop devices */

    #if EMBEDDED_ENABLE
        #define NTP_ENABLE            (1)        /* set to 1 to allow using NTP for real world time functions*/
        #define MAX_FILE_NAME)SIZE    (20)    /* maximum length of a filename */

        /* define your architecture to 1 here */
        #define ESP32_ARDUINO         (1)        /* set to 1 to use ESP32 */

    #endif

#endif