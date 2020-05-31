#include <windows_lib.h>
#include <keyboard_lib.h>
#include <malloc.h>
#include <userlib.h>
#include <windows.h>


Window *w2;

static void createWindow(){

	w2 = (Window *) malloc(sizeof(Window));

	w2->xi = getRes()->width/2; w2->xf = getRes()->width;
    w2->yi = 0; w2->yf = getRes()->height;

	w2->cursors[titleCursor].x=titleX;	w2->cursors[titleCursor].y=titleY;
	w2->cursors[titleCursor].fontColor=titleColor;	w2->cursors[titleCursor].fontSize=titleSize;

	w2->cursors[bodyCursor].x=0;	w2->cursors[bodyCursor].y=bodyY;
	w2->cursors[bodyCursor].fontColor=bodyColor;	w2->cursors[bodyCursor].fontSize=bodySize;

}


void initWindow2(){

	createWindow();
	setWindow(w2);

	w2->activeCursor = titleCursor;
	printLine("Window 2");

}


static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


void window2(){

	setWindow(w2);
	drawIndicator(indicatorColor);
	

	w2->activeCursor = bodyCursor;
	while(1){

		char c = getChar();

		if(c==f1Code){
			drawIndicator(0);
			return;
		}

		printChar(c);

	}

}