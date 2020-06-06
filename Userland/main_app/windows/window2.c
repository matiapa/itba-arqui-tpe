#include <windows_lib.h>
#include <keyboard_lib.h>
#include <userlib.h>
#include <windows.h>
#include <syscalls.h>


/* --------------------------------------------------------------------------------------------------------------------------
                                        		WINDOW DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */

static Window w;
#define cursor w2.cursors[w2.activeCursor]
#define NEWLINE 13


/* --------------------------------------------------------------------------------------------------------------------------
                                        		SHELL DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */

typedef enum{
	NOCOMMAND,
	CPUTEMP,
	HELP,
	MEMDUMP,
	MPDATA,
	REGDUMP,
	TIME
} command;


command setCommand(char * buffer, int length, char * string);

void printCPUTemp(void);
void help(void);
void printMemDump(char *start);
void printMPInfo(void);
void printRegDump(void);
void printTime(void);

static void printWarning(int num);

/* --------------------------------------------------------------------------------------------------------------------------
                                        	WINDOW METHODS
------------------------------------------------------------------------------------------------------------------------- */

static void createWindow(){

	ScreenRes res;
	getRes(&res);

	w.xi = res.width/2; w.xf = res.width;
    w.yi = 0; w.yf = res.height;

	w.cursors[titleCursor].x=titleX;	w.cursors[titleCursor].y=titleY;
	w.cursors[titleCursor].fontColor=titleColor;	w.cursors[titleCursor].fontSize=titleSize;

	w.cursors[bodyCursor].x=0;	w.cursors[bodyCursor].y=bodyY;
	w.cursors[bodyCursor].fontColor=bodyColor;	w.cursors[bodyCursor].fontSize=bodySize;

}


void initWindow2(){

	createWindow();
	setWindow(&w);

	for(int x=w.xi; x<w.xf; x++){
        for(int y=w.yi; y<w.yf; y++){
            draw(x, y, 0x000000);
        }
    }

	w.activeCursor = titleCursor;
	printLine("Shell");

}


static void drawIndicator(int color){

	for(int x=indicatorX; x<indicatorWidth; x++)
		drawPoint(x, indicatorY, indicatorHeight, color);

}


void window2(){

	setWindow(&w);
	drawIndicator(indicatorColor);
	
	newLine();
	char bufferw2[BUFFERW2+1];
	int bw2Iter = 0;
	command currentCommand = NOCOMMAND;

	w.activeCursor = bodyCursor;

	while(1){

		char c = getChar();
		
		if(c==f1Code){
			drawIndicator(0);
			return;
		}

		if(bw2Iter < BUFFERW2) {
			bufferw2[bw2Iter++] = c;
			if (bw2Iter==BUFFERW2)
				bufferw2[bw2Iter++] = 0;
		}

		printChar(c);

		if (c == NEWLINE) {
			char parameter[BUFFERW2];

			if (bw2Iter > BUFFERW2)
				currentCommand = NOCOMMAND;
			else {
				bufferw2[bw2Iter] = 0;
				currentCommand = setCommand(bufferw2, bw2Iter, parameter);
			}
			
			switch(currentCommand) {
				case CPUTEMP:
					printCPUTemp();
					break;
				case HELP:
					help();
					break;
				case MEMDUMP:	//fix
					printMemDump((char *) 8);
					break;
				case MPDATA:
					printMPInfo();
					break;
				case REGDUMP:
					printRegDump();
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


/* --------------------------------------------------------------------------------------------------------------------------
                                        SHELL METHODS
------------------------------------------------------------------------------------------------------------------------- */

const int bufferText = 70;
const int bufferMem = 33;


void printMPInfo(void) {
    CPUInfo info;

	char brandName[50], brandDesc[70];
    info.brandName = (char *) &brandName;
    info.brandDesc = (char *) &brandDesc;

    cpuInfo(&info);

    printf("\\nBrand name: %s", 1, info.brandName);
    printf("\\nBrand description: %s\\n", 1, info.brandDesc);
}


void printCPUTemp(void) {
    int temp = cpuTemp();
    printf("\\n Computer's Temperature in Celcius: %d\\n", 1, temp);
}


void printTime(void) {
    Time t ;
    getTime(&t);

    printf("\\nTime now: %d:%d:%d\\n", 3, t.hours, t.minutes, t.seconds);
}


void printRegDump(void) {
    RegDump reg;
    regDump(&reg);

    printLine("Register's values:");
    printLine("--- --- --- --- --- --- --- --- --- --- --- --- ---");
    printf("\\n - rax - %x", 1, reg.rax);
    printf("\\n - rbx - %x", 1, reg.rbx);
    printf("\\n - rcx - %x", 1, reg.rcx);
    printf("\\n - rdx - %x", 1, reg.rdx);
    printf("\\n - rsi - %x", 1, reg.rsi);
    printf("\\n - rdi - %x", 1, reg.rdi);
    printf("\\n - rbp - %x", 1, reg.rbp);
    printf("\\n - rsp - %x\\n", 1, reg.rsp);

    printf("\\n - r8 - %x", 1, reg.r8);
    printf("\\n - r9 - %x", 1, reg.r9);
    printf("\\n - r10 - %x", 1, reg.r10);
    printf("\\n - r11 - %x", 1, reg.r11);
    printf("\\n - r12 - %x", 1, reg.r12);
    printf("\\n - r13 - %x", 1, reg.r13);
    printf("\\n - r14 - %x", 1, reg.r14);
    printf("\\n - r15 - %x\\n", 1, reg.r15);

    printLine("--- --- --- --- --- --- --- --- --- --- --- --- ---");
}


void printMemDump(char * start) {   //TODO
	char src[bufferMem];
    char dest[bufferMem];
	
    dest[bufferMem-1] = src[bufferMem-1]+1;
    memDump(src, dest);

    newLine();
    for(int i=0; i<bufferMem; i++) {
        printf(" - %x\\n",1,src[i]);
    }
}


void help(void) {
    newLine();
    printLine("On this Terminal you can try the following commands:");
    printLine(" --- --- --- --- --- --- --- --- --- --- --- --- ---");

    printLine(" - cputemp    to get the Computer's Temperature");
    printLine(" - help       to go to the Help Manual");
    printLine(" - memdata n  to print Memory starting with address n");
    printLine(" - mpdata     to get the Microprocessor's Brand Data");
    printLine(" - regdata    to get the Register's Values");
    printLine(" - time       to get the Time");

    printLine(" --- --- --- --- --- --- --- --- --- --- --- --- ---");
    newLine();
}


static void printWarning(int num) {
    printf("\\n >> Error: ", 0);
    switch(num) {
        case 0:    
            printLine("Command not found");
            printLine("If you want to see the command manual type 'help'.");
        break;
        default: 
            print("Something went wong. ");
    }
    printf("Please, try again.\\n\\n",0);
}

/* --------------------------------------------------------------------------------------------------------------------------
                                COMMAND-CHECK METHODS
------------------------------------------------------------------------------------------------------------------------- */


static int isCommandTemp(char * buffer, int length) {
    //strncmp();
    return 1;
}
static int isCommandHelp(char * buffer, int length) {
    return 1;
}
static int isCommandMemdump(char * buffer, int length, char * start) {
    return 1;
}
static int isCommandProcdata(char * buffer, int length) {
    return 1;
}
static int isCommandRegdata(char * buffer, int length) {
    return 1;
}
static int isCommandTime(char * buffer, int length) {
    return 1;
}


static int isAllowedChar(char c) {
    if (isAlpha(c) || isDigit(c) || isDecimalPoint(c) || isSpace(c))
        return 1;
    return 0;
}

command setCommand(char * buffer, int length, char * string) {

    for (int i=0; i< length; i++) {
        if (!isAllowedChar(buffer[i]))
            return NOCOMMAND;
        buffer[i] = toLower(buffer[i]);
    }

    if (isCommandTemp(buffer, length))
        return CPUTEMP;
    if (isCommandHelp(buffer, length))
        return HELP;
    if (isCommandMemdump(buffer, length, string))
        return MEMDUMP;

    if (isCommandProcdata(buffer, length))
        return MPDATA;
    if (isCommandRegdata(buffer, length))
        return REGDUMP;
    if (isCommandTime(buffer, length))
        return TIME;
    
    return NOCOMMAND;
}