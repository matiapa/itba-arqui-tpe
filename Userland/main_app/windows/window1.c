#include <windows_lib.h>
#include <keyboard_lib.h>
#include <malloc.h>
#include <windows.h>

#define NULL ((void *) 0)
#define titleCursor 0
#define bodyCursor 1

#define cursor w1->cursors[w1->activeCursor]

Window *w1;

static void createWindow(){

	w1 = (Window *) malloc(sizeof(Window));

	w1->xi = 0; w1->xf = getRes()->width/2;
    w1->yi = 0; w1->yf = getRes()->height;

	w1->cursors[titleCursor].x=titleX;	w1->cursors[titleCursor].y=titleY;
	w1->cursors[titleCursor].fontColor=titleColor;	w1->cursors[titleCursor].fontSize=titleSize;

	w1->cursors[bodyCursor].x=0;	w1->cursors[bodyCursor].y=bodyY;
	w1->cursors[bodyCursor].fontColor=bodyColor;	w1->cursors[bodyCursor].fontSize=bodySize;

}


static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


void initWindow1(){

	createWindow();
	setWindow(w1);

	w1->activeCursor = titleCursor;
	printLine("Window 1");

	for(int y=0; y<w1->yf; y++)
		drawPoint(w1->xf-10, y, 2, 0x00FF00);

}


void window1(){

	setWindow(w1);
	drawIndicator(indicatorColor);

	w1->activeCursor = bodyCursor;
	while(1){

		char c = getChar();

		if(c==f2Code){
			drawIndicator(0);
			return;
		}

		printChar(c);

	}

}