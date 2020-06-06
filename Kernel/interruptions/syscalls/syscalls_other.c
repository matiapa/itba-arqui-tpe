#include <keyboard_driver.h>
#include <rtc_driver.h>
#include <stdint.h>

int sysRead(char *str, int fd){

    return read();

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

// ---------------------------------------------------------------------------------------------------------------------------

typedef struct RegBkp{
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, r8, r9, r10, r11, r12, r13, r14, r15;
} RegBkp;

void dumpState(RegBkp *dest);

void sysGetRegBkp(RegBkp *dest){

    dumpState(dest);

}