#include <programs.h>
#include <windows_lib.h>
#include <kernel_messages.h>
#include <keyboard_lib.h>

int interruption(va_list valist){

    int id = va_arg(valist, int);

    if(id == TIMER_TICK_IRQ){
        winTimerTickListener();
    }

    if(id == KEYBOARD_IRQ){
        int keyCode = va_arg(valist, int);
        keyboardListener(keyCode);
    }

    return 1;

}