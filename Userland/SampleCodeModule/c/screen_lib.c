#include <font.h>

// struct ScreenRes{
//     int height;
//     int width;
// }

// struct ScreenRes * getRes();

const int HEIGHT = 1920;
const int WIDTH = 780;

/* --------------------------------------------------------------------------------------------------------------------------
                                            VIDEO METHODS
-------------------------------------------------------------------------------------------------------------------------- */

void draw(int cx, int cy, int rgb);


void drawPoint(int x, int y, int size, int rgb){

    for(int cx=x; cx<x+size; cx++){
        for(int cy=y; cy<y+size; cy++){
            draw(cx, cy, rgb);
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

const int fontWidth = 8;
const int fontHeight = 8;
 
int fontSize = 2;
int fontColor = 0x00FF00;
int charSpacing = 1;
int lineSpacing = 1;

int textX=0, textY=0;


void setColor(int newColor){

	fontColor = newColor;

}


void clearScreen(){

    for(int x=0; x<WIDTH; x++){
        for(int y=0; y<HEIGHT; y++){
            draw(x, y, 0);
        }
    }

    textX=0; textY=0;

}


void forwardCursor(){

    textX += fontWidth*fontSize+charSpacing;

    if(textX > WIDTH){
        textX = 0;
        textY += fontHeight*fontSize+lineSpacing;
    }

    if(textY > HEIGHT){
        textY = 0;
        clearScreen();
    }

}


void backwardCursor(){

    textX -= fontWidth*fontSize+charSpacing;

    if(textX < 0){
        textX = 0;
    }

}


void newLine(){

    textX = 0;
    textY += fontHeight*fontSize+lineSpacing;

}


void printChar(char c){

    // Carriage return
    if(c==13){
        newLine();
        return;
    }

    // Backspace
    if(c==8){
        backwardCursor();
        drawPoint(textX, textY, fontSize*fontHeight, 0);
        return;
    }

    // Not printable
    if(c<32 || c>127)
        return;

    drawChar(textX, textY, c, fontSize, fontColor);

    forwardCursor();

}


void print(char s[]){

    for(int i=0; s[i]!=0; i++)
        printChar(s[i]);

}


void printLine(char s[]){
	
    print(s);
    newLine();

}