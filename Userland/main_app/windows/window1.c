#include <windows_lib.h>
#include <keyboard_lib.h>
#include <windows.h>
#include <userlib.h>
#include <syscalls.h>
#include <stdint.h>

#define NULL ((void *) 0)
#define titleCursor 0
#define bodyCursor 1

#define cursor w1.cursors[w1.activeCursor]

void calculateString(char *s);
void printWarning(int num);


static Window w;

void createWindow(){

	ScreenRes res;
	getRes(&res);

	w.xi=0; w.xf=res.width/2;
    w.yi=0; w.yf=res.height;

	w.cursors[titleCursor].x=titleX;	w.cursors[titleCursor].y=titleY;
	w.cursors[titleCursor].fontColor=titleColor;	w.cursors[titleCursor].fontSize=titleSize;

	w.cursors[bodyCursor].x=0;	w.cursors[bodyCursor].y=bodyY;
	w.cursors[bodyCursor].fontColor=bodyColor;	w.cursors[bodyCursor].fontSize=bodySize;

}


static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


void initWindow1(){

	createWindow();	
	setWindow(&w);

	for(int x=w.xi; x<w.xf; x++){
        for(int y=w.yi; y<w.yf; y++){
            draw(x, y, 0x000000);
        }
    }

	w.activeCursor = titleCursor;
	printLine("Calculator");

	for(int y=0; y<w.yf; y++)
		drawPoint(w.xf-10, y, 2, 0x00FF00);

}


void window1(){

	setWindow(&w);
	drawIndicator(indicatorColor);

	w.activeCursor = bodyCursor;

	while(1){

		char c = getChar();

		if(c==f2Code){
			drawIndicator(0);
			return;
		}

		printChar(c);

		if (c == '=') {
			newLine();
			
			char * aux = "9.8x3+2=";
			calculateString(aux);
		}

	}

}


/* --------------------------------------------------------------------------------------------------------------------------
                                        CALCULATOR METHODS
------------------------------------------------------------------------------------------------------------------------- */

void calculateString(char * s) {

    double result = 324.32;
    
    print(" >> ");
    printf("%f", 1, result);

}


void printWarning(int num) {
    printf("\\n >> Error: ", 0);
    switch(num) {
        case 1: print("Zero division is not allowed.");
        break;
        case 2: print("To calculate use only numbers or the following operators: ");
        printLine("+ - * / ( ) , .");
        break;
        default: print("Something went wong.");
    }
    printLine(" Please, try again.");
}