#include <windows_lib.h>
#include <keyboard_lib.h>
#include <malloc.h>
#include <userlib.h>
#include <windows.h>
#include <syscalls.h>

#define cursor w2->cursors[w2->activeCursor]
#define NEWLINE 13

Window *w2;

static void createWindow(){

	w2 = (Window *) malloc(sizeof(Window));

	ScreenRes * res = (ScreenRes *) malloc(sizeof(ScreenRes));
	getRes(res);

	w2->xi = res->width/2; w2->xf = res->width;
    w2->yi = 0; w2->yf = res->height;

	w2->cursors[titleCursor].x=titleX;	w2->cursors[titleCursor].y=titleY;
	w2->cursors[titleCursor].fontColor=titleColor;	w2->cursors[titleCursor].fontSize=titleSize;

	w2->cursors[bodyCursor].x=0;	w2->cursors[bodyCursor].y=bodyY;
	w2->cursors[bodyCursor].fontColor=bodyColor;	w2->cursors[bodyCursor].fontSize=bodySize;

}


void initWindow2(){

	createWindow();
	setWindow(w2);

	w2->activeCursor = titleCursor;
	printLine("Shell");

}


static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


void window2(){

	setWindow(w2);
	drawIndicator(indicatorColor);
	
	newLine();
	char bufferw2[BUFFERW2];
	int bw2Iter = 0;
	command currentCommand = NOCOMMAND;

	w2->activeCursor = bodyCursor;
	while(1){

		char c = getChar();
		
		if(c==f1Code){
			drawIndicator(0);
			return;
		}

		if (bw2Iter == BUFFERW2 && c!=NEWLINE)
			bw2Iter++;
		else if(bw2Iter < BUFFERW2)
			bufferw2[bw2Iter++] = c;

		printChar(c);

		if (c == NEWLINE) {
			char parameter[BUFFERW2];

			if (bw2Iter > BUFFERW2)
				currentCommand = NOCOMMAND;
			else {
				currentCommand = setCommand(bufferw2, bw2Iter, parameter);
			}
			
			switch(currentCommand) {
				case CPUTEMP:
					printCPUtemp();
				break;
				case HELP:
					help();
				break;
				case MEMDUMP:	//fix
					printMemdump(parameter);
				break;
				case MPDATA:
					printMPinfo();
				break;
				case REGDUMP:
					printRegdump();
				break;
				case TIME:
					printTime();
				break;
				default:
					printWarning(NOCOMMAND);
			}

			bw2Iter = 0;
		}

	}

}


void cmdRegDump(){
	RegDump * dump = malloc(sizeof(RegDump));
    regDump(dump);

	printf("RAX: %x\\n", 1, dump->rax);
    printf("RBX: %x\\n", 1, dump->rbx);
    printf("RCX: %x\\n", 1, dump->rcx);
    printf("RDX: %x\\n\\n", 1, dump->rdx);

    printf("RSI: %x\\n", 1, dump->rsi);
    printf("RDI: %x\\n\\n", 1, dump->rdi);

    printf("RSP: %x\\n", 1, dump->rsp);
    printf("RBP: %x\\n\\n", 1, dump->rbp);

    printf("RIP: %x\\n", 1, dump->rip);
}