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

### Usage

Copy the following files into your working directory:

```c
1. config.h
2. logga.h
3. logga.cpp

```

### Desktop
#### 1. Create logging object 

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