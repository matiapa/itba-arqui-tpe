/*---------------------------------------------------------------------------------------------------
|   WINDOW_1.C    |                                                                             	|
|----------------------                                                                             |
| This windows will display the calculator program.													|
| Press ENTER to calculate an expression.															|
| Press DEL to drop the current expression.															|
| Press F2 to switch to shell program.																|
---------------------------------------------------------------------------------------------------*/

#include <windows_lib.h>
#include <keyboard_lib.h>
#include <std_lib.h>
#include <syscalls.h>
#include <stdint.h>

/* --------------------------------------------------------------------------------------------------------------------------
                                        		WINDOW DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */

static Window w;


/* --------------------------------------------------------------------------------------------------------------------------
                                        		CALCULATOR DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */


static void calculateString(char *s);
static void printWarning(int num);

/* -----------------------------------------------------------
 Defines the position and size of the window (all left half)
 and assings a color to title and body cursors
-------------------------------------------------------------- */

static void createWindow(){

	ScreenRes res;
	getRes(&res);

	w.xi=0; w.xf=res.width/2;
    w.yi=0; w.yf=res.height;

	w.cursors[titleCursor].x=titleX;	w.cursors[titleCursor].y=titleY;
	w.cursors[titleCursor].fontColor=titleColor;	w.cursors[titleCursor].fontSize=titleSize;

	w.cursors[bodyCursor].x=0;	w.cursors[bodyCursor].y=bodyY;
	w.cursors[bodyCursor].fontColor=bodyColor;	w.cursors[bodyCursor].fontSize=bodySize;

}


/* -----------------------------------------------------------
 Draws a line below the title to indicate that this windows
 is currently selected
-------------------------------------------------------------- */

static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


/* -----------------------------------------------------------
 Creates the window, draws the title, and a separator on the
 right end of the window.
-------------------------------------------------------------- */

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


/* -------------------------------------------------------------
 Method that activates when this window becomes selected
 it waits for a key press constantly and handles it appropiately
---------------------------------------------------------------- */

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

		if(c==suprCode){

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


static void printWarning(int num) {
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