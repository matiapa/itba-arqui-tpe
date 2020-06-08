#include <keyboard_driver.h>

#define BUFFER_LEN 8

int buffer[BUFFER_LEN];
int pos=-1;

void keyPressed(){
    buffer[++pos] = read();
}

int getKey(){
    return pos>=0 ? buffer[pos--] : -1;
}