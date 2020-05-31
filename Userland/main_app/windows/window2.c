#include <windows_lib.h>
#include <keyboard_lib.h>
#include <malloc.h>
#include <userlib.h>

#define NULL ((void *) 0)
#define titleCursor 0
#define bodyCursor 1

#define cursor w2->cursors[w2->activeCursor]

Window *w2;

static void createWindow(){

	w2 = (Window *) malloc(sizeof(Window));

	// w2->xi = getRes()->width/2; w2->xf = getRes()->width;
    // w2->yi = 0; w2->yf = getRes()->height;
	
	w2->xi = 512; w2->xf = 1024;
	w2->yi = 0; w2->yf = 712;

	w2->cursors[titleCursor].x=0;	w2->cursors[titleCursor].y=0;
	w2->cursors[titleCursor].fontColor=0x00FF00;	w2->cursors[titleCursor].fontSize=2;

	w2->cursors[bodyCursor].x=0;	w2->cursors[bodyCursor].y=50;
	w2->cursors[bodyCursor].fontColor=0xFFFFFF;	w2->cursors[bodyCursor].fontSize=1;

}


void initWindow2(){

	createWindow();
	setWindow(w2);

	w2->activeCursor = titleCursor;
	printLine("Window 2");

}


void window2(){

	setWindow(w2);

	w2->activeCursor = bodyCursor;
	while(1){

		char c = getChar();

		if(c==f1Code)
			return;

		printChar(c);

	}

}