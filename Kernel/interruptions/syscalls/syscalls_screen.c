#include <screen_driver.h>
#include <lib.h>

typedef struct ScreenRes{
    int height;
    int width;
} ScreenRes;


void sysDraw(int cx, int cy, int rgb){

    draw(cx, cy, rgb);

}


ScreenRes * res = 0;

ScreenRes * sysGetRes(){

    res = res==0 ? malloc(8) : res;    
    
    res->height = getResHeight();
    res->width = getResWidth();

    return res;

}