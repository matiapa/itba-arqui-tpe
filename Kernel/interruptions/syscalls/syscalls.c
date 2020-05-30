#include <screen_driver.h>
#include <keyboard_driver.h>
#include <lib.h>

struct ScreenRes{
    int height;
    int width;
};


void syscallDraw(int cx, int cy, int rgb){

    draw(cx, cy, rgb);

}


int syscallRead(char *str, int fd){

    return read();
    return 1;

}


struct ScreenRes * res = 0;

struct ScreenRes * syscallGetRes(){

    res = res==0 ? malloc(8) : res;    
    
    res->height = getResHeight();
    res->width = getResWidth();

    return res;

}