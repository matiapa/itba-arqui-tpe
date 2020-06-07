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
#define W1_BUFFER_LEN 250

typedef enum{
	CORRECT,
	DIVZERO,
	WRONG_CALC_CHAR,
	WRONG_DECIMAL,
	WRONG_PARENTH,
	WRONG
} message;

/* --------------------------------------------------------------------------------------------------------------------------
                                        		CALCULATOR DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */


static void calculateString(char *s, int length);
static void printWarning(message num);
static int isAllowedChar(char c);
static int checkAllowedChars(char * s, int length);
double calcExp(char *, int, message *);

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

	newLine();
	char bufferw1[W1_BUFFER_LEN+1];
	cleanBuffer(bufferw1,W1_BUFFER_LEN);
	int bIter = 0;

	w.activeCursor = bodyCursor;

	while(1){

		char c = getChar();

		if(c==f2Code){
			drawIndicator(0);
			return;
		}

		if (c==escCode) {
			clearLine();
			cleanBuffer(bufferw1,W1_BUFFER_LEN);
			bIter=0;
		}
		else if(c=='\b') {
			if (bIter!=0) {
				bIter--;
				bufferw1[bIter] = 0;
			}
		}
		else if(bIter < W1_BUFFER_LEN) {
			bufferw1[bIter++] = c;
			bufferw1[bIter] = 0;
			if (bIter==W1_BUFFER_LEN)
				bIter++;
		}

		printChar(c);

		if (c == '=' || c=='\r') {
			newLine();
			if (bIter > W1_BUFFER_LEN)
				printWarning(WRONG);
			else {
				calculateString(bufferw1,bIter-1);
			}

			cleanBuffer(bufferw1,W1_BUFFER_LEN);
			bIter = 0;
		}

	}

}


/* --------------------------------------------------------------------------------------------------------------------------
                                        CALCULATOR METHODS
------------------------------------------------------------------------------------------------------------------------- */

void calculateString(char * s, int length) {

	if (!checkAllowedChars(s,length)) {
		printWarning(WRONG_CALC_CHAR);
		return;
	}

	message outputMsg = CORRECT;
	double result = calcExp(s, length, &outputMsg);

	if(outputMsg!=CORRECT) {
		printWarning(outputMsg);
	}
	else {
		printf(" >> %f\\n", 1, result);
	}

}

static int checkAllowedChars(char * s, int length) {
	for(int i=0; i<length; i++) {
		if(!isAllowedChar(s[i]))
			return 0;
	}
	return 1;
}

static int isAllowedChar(char c) {
	if (isDigit(c) || isOperator(c) || isSpace(c) || isDecimalPoint(c))
		return 1;

	return 0;
}

double calcExp(char *str, int length, message * outputMsg) {
	double result;

	return result;
}

/* -------------------------------------------------------------
						WARNING
---------------------------------------------------------------- */

static void printWarning(message msg) {
    printf("\\n >> Error: ", 0);

    switch(msg) {
        case DIVZERO: 
			print("Zero division is not allowed.");
        break;
        case WRONG_CALC_CHAR: 
			print("To calculate use only numbers or the following operators: ");
    	    printLine("+ - x % ( ) , .");
        break;
		case WRONG_DECIMAL:
			printLine("A number can have up to one decimal point.");
		case WRONG_PARENTH:
			printLine("Every opening parenthesis needs to find a closing one, in that order");
		break;
        default: print("Something went wrong.");
    }

    printLine(" Please, try again.");
}