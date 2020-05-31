#include <keyboard_driver.h>
#include <rtc_driver.h>

int sysRead(char *str, int fd){

    return read();
    return 1;

}

// ---------------------------------------------------------------------------------------------------------------------------

typedef struct Time{
    int hours, minutes, seconds;
} Time;


void sysGetTime(Time * time){

    time->hours = getHours();
    time->minutes = getMinutes();
    time->seconds = getSeconds();

}