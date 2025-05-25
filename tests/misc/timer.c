#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <error.h>
#include <sys/time.h>

//char* rfc8601_timespec(struct timespec* tv) {
//    char time_str[127];
//    double fractional_seconds;
//    int milliseconds;
//    struct tm tm; // broken down time
//    char* rfc8601;
//
//    rfc8601 = malloc(256);
//
//    memset(&tm, 0, sizeof(struct tm));
//    sprintf(time_str, "%ld UTC", tv->tv_sec);
//
//    // convert our timespec into broken down time
//    strptime(time_str, "%s %U", &tm); // bug: STRPTIME NOT AVAILABLE ON WINDOWS
//
//    // do the math to convert nanonseconds to integer milliseconds
//    fractional_seconds = (double) tv->tv_nsec;
//    fractional_seconds /= 1e6;
//    fractional_seconds = round(fractional_seconds);
//    milliseconds = (int) fractional_seconds;
//
//    // print the date and time without milliseconds
//    strftime(time_str, sizeof(time_str), "%Y-%m-%d%T%H:%M:%S", &tm);
//
//    // add on the fractional seconds and Z for the UTC Timezone
//    sprintf(rfc8601, "%s.%dZ", time_str, milliseconds);
//
//    return  rfc8601;
//
//}

int main() {
    /* epoch time */
    struct timespec tv;
    if(clock_gettime(CLOCK_REALTIME, &tv)) {
        perror("error clock_gettime\n");
    }

    //printf("seconds since epoch: %lu \n", tv.tv_sec);

    /* get time of day from sys/time.h*/
    struct timeval ts;
    gettimeofday(&ts, NULL); // return value can be ignored
    printf("Time of day: sec: %lu microsec: %lu \n", ts.tv_sec, ts.tv_usec);

    /* time in ISO 8601 formatted timestamp */
    char* rfc8601;
    if(clock_gettime(CLOCK_REALTIME, &tv)) {
        perror("Error clock gettime\n");
    }

    return 0;
}
