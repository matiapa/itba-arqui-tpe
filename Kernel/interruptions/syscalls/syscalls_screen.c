#include <screen_driver.h>
#include <lib.h>
#include <stdint.h>


void sysDraw(int cx, int cy, int rgb){

    draw(cx, cy, rgb);

}

// ---------------------------------------------------------------------------------------------------------------------------

typedef struct ScreenRes{
    int height;
    int width;
} ScreenRes;


void sysGetRes(ScreenRes * res){
    
    res->height = getResHeight();
    res->width = getResWidth();

}