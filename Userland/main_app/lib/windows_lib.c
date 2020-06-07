/*---------------------------------------------------------------------------------------------------
|   WINDOWS_LIB.C    |                                                                              |
|---------------------                                                                              |
| This libary implements all the needed functions for a window to work, such as methods for drawing |
  and writing on its own space. Also, it handles the work of managing which is the selected screen  |
---------------------------------------------------------------------------------------------------*/

#include <windows_lib.h>
#include <std_lib.h>
#include <font.h>
#include <syscalls.h>


/* --------------------------------------------------------------------------------------------------------------------------
                                            WINDOWS METHODS
-------------------------------------------------------------------------------------------------------------------------- */

static Window *window;


void setWindow(Window *currWindow){
    window=currWindow;
}


#define cursor window->cursors[window->activeCursor]

#define height window->yf-window->yi

#define width window->xf-window->xi


/* --------------------------------------------------------------------------------------------------------------------------
                                            DRAW METHODS
-------------------------------------------------------------------------------------------------------------------------- */


void drawPoint(int x, int y, int size, int rgb){

    int absx = window->xi + x;
    int absy = window->yi + y;

    for(int x=absx; x<absx+size; x++){
        for(int y=absy; y<absy+size; y++){
            draw(x, y, rgb);
        }
    }

}


void drawChar(int x, int y, char c, int size, int rgb) {

    for (int col=0; col<8; col++) {
        for (int row=0; row<8; row++) {
            if(font8x8_basic[(int) c][col] & 1 << row){
                drawPoint(x+row*size, y+col*size, size, rgb);
            }
        }
    }

}


/* --------------------------------------------------------------------------------------------------------------------------
                                            TEXT METHODS
-------------------------------------------------------------------------------------------------------------------------- */
 
#define charSpacing 1;
#define lineSpacing 1;


void clearScreen(){

    for(int x=window->xi; x<window->xf; x++){
        for(int y=window->yi; y<window->yf; y++){
            draw(x, y, 0);
        }
    }

}


void clearLine(){

	for(int x=window->xi; x<(window->xf - fontHeight*cursor.fontSize - 4); x++){
		drawPoint(x, cursor.y, fontHeight*cursor.fontSize, 0);
	}

    cursor.x = 0;

}


static void nextChar(){

    cursor.x += cursor.fontSize*fontWidth+charSpacing;

    if(cursor.x > width){
        cursor.x = 0;
        cursor.y += cursor.fontSize*fontHeight+lineSpacing;
    }

    if(cursor.y > height){
        cursor.y = 0;
        clearScreen();
    }

}


static void prevChar(){

    cursor.x -= cursor.fontSize*fontWidth+charSpacing;

    if(cursor.x < 0){
        cursor.x = 0;
    }

}


void newLine(){

    cursor.x = 0;
    cursor.y += cursor.fontSize*fontWidth+lineSpacing;

}


void printChar(char c){

    // Carriage return
    if(c==13){
        newLine();
        return;
    }

    // Backspace
    if(c==8){
        prevChar();
        drawPoint(cursor.x, cursor.y, cursor.fontSize*fontHeight, 0);
        return;
    }

    // Not printable
    if(c<32 || c>127)
        return;

    drawChar(cursor.x, cursor.y, c, cursor.fontSize, cursor.fontColor);

    nextChar();

}


void print(char s[]){

    for(int i=0; s[i]!=0; i++)
        printChar(s[i]);

}


void printLine(char s[]){
	
    print(s);
    newLine();

}


void cleanBuffer(char * buffer, int len) {

	for (int j=0; j<len; j++)
		buffer[j] = 0;
}