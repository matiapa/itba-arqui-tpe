#include <windows_lib.h>
#include <keyboard_lib.h>
#include <malloc.h>

#define NULL ((void *) 0)
#define titleCursor 0
#define bodyCursor 1

#define cursor w1->cursors[w1->activeCursor]

Window *w1;

static void createWindow(){

	w1 = (Window *) malloc(sizeof(Window));

	w1->xi = 0; w1->xf = getRes()->width/2;
    w1->yi = 0; w1->yf = getRes()->height;

	w1->cursors[titleCursor].x=0;	w1->cursors[titleCursor].y=0;
	w1->cursors[titleCursor].fontColor=0x00FF00;	w1->cursors[titleCursor].fontSize=2;

	w1->cursors[bodyCursor].x=0;	w1->cursors[bodyCursor].y=50;
	w1->cursors[bodyCursor].fontColor=0xFFFFFF;	w1->cursors[bodyCursor].fontSize=1;

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

	w1->activeCursor = bodyCursor;
	while(1){

		char c = getChar();

		if(c==f2Code)
			return;

		printChar(c);

	}

}