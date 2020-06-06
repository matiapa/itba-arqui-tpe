#include <lib.h>

static void * const mainAppAddress = (void*)0x400000;

int sysMemDump(void *src, void *dest){

    if(dest<mainAppAddress)
        return -1;

    memcpy(dest, src, 32);
    return 0;

}