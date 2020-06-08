#include <programs.h>
#include <windows_lib.h>
#include <kernel_messages.h>

static int x = 0;

int interruption(int message){

    draw(x, 100, 0xFF0000);

    x += 1;

    if(message == TIMER_TICK_INT){
        winTimerTickListener();
    }

    return 1;

}