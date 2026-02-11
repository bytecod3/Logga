# Logga
![Static Badge](https://img.shields.io/badge/stage-development-green)
![Static Badge](https://img.shields.io/badge/license-MIT-orange)
![Static Badge](https://img.shields.io/badge/version-v1-white)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/bytecod3/Logga)

A minimalistic data and event logging library built for both embedded and mainstream C programs

### Features 
- Basic logging (TRACE, INFO, WARNING, CRITICAL, etc)
- Supports real-world time via NTP
- Support CPU time 
- File size check 
- Cyclic logging
- Network log data dump 
- JSON format support
- Fetch logs between specific periods of time/date etc
- Follows MISRA-C standard

### How it works
#### Embedded
1. To do basic logging, this library checks the config.h file to know which framework you are using. For devices that are not connected to the internet, you can enable and disable NTP by modifying the config.h header.(see example below)

2. You can log into both the internal device memory, if your device has enough internal memory, such as NVS for ESP32, or you can use SD card to do the logging. 





### Usage

Copy the following files into your working directory:

```c
1. config.h
2. logga.h
3. logga.cpp

```

### Embedded
#### PlatformIO
If using platformio for your project, follow the steps below:
1. Copy the following files into your project root. You can put them in ```include``` and ```src``` folders respectively
```
1. logga.h
2. logga.cpp
3. config.h
```
2. Include ```logga.h``` into your main.
```
#include "logga.h
```


### Desktop
#### Create logging object 

The code below shows how to create logging object:
```c

yourfile.cpp


#include <iostream>
#include <stdint.h>
#include "logga.h"

//#define NLOG / to turn  on/off logging **/

#ifndef NLOG

#define LOG_FILE_SIZE
Logga_Type_t system_logger = create_logga(); /* create logger object */
const char* filename = "/log-file.log"; /* your logging filename */

#endif

int main() {
    #ifndef NLOG
        init_logga(system_logger, filename);
    #endif
    
    return 0;
}


```



## Tests Done 
### ESP32 
#### SPIFFS init
--- 
The library should work automatically with spiffs when using an ESP32 
If the ESP32 SPIFFS is not recognized, please use the following resource to 
fix the issue: 
!(Set up spiffs on ESP32)[https://www.programmingelectronics.com/spiffs-esp32/]


### Known issues