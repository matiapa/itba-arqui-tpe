#include <screen_driver.h>
// #include <keyboard_driver.h>

void syscallDraw(int cx, int cy, int rgb){

    draw(cx, cy, rgb);

}


int syscallRead(char *str, int fd){

    //return read();
    return 1;

}