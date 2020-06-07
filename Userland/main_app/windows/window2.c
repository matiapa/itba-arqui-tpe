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
	TIME,
	WRONG
} command;


command setCommand(char * buffer, int length, char * string);

void printCPUTemp(void);
void help(void);
void printMemDump(char *start);
void printMPInfo(void);
void printRegDump(void);
void printTime(void);

static void printWarning(int num);
static int parseHexa(char *);

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
	cleanBuffer(bufferw2);
	int bw2Iter = 0;
	command currentCommand = WRONG;

	w.activeCursor = bodyCursor;

	while(1){

		char c = getChar();
		
		if(c==f1Code){
			drawIndicator(0);
			return;
		}

		if(c=='\b') {
			if (bw2Iter!=0) {
				bw2Iter--;
				bufferw2[bw2Iter] = 0;
			}
		}
		else if(bw2Iter < BUFFERW2) {
			bufferw2[bw2Iter++] = c;
			bufferw2[bw2Iter] = 0;
			if (bw2Iter==BUFFERW2)
				bw2Iter++;
		}

		printChar(c);

		if (c == NEWLINE) {
			char parameter[BUFFERW2];

			if (bw2Iter > BUFFERW2)
				currentCommand = WRONG;
			else {
				currentCommand = setCommand(bufferw2, bw2Iter, parameter);
			}

			switch(currentCommand) {
				case CPUTEMP:
					printCPUTemp();
					break;
				case HELP:
					help();
					break;
				case MEMDUMP:
					printMemDump(parameter);
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
				case WRONG:
					printWarning(WRONG);
				default:
					printWarning(NOCOMMAND);
			}
			cleanBuffer(bufferw2);	
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


void printMemDump(char * start) {

	int res = parseHexa(start);
	if(res < 0) {
		printLine("Parameter not allowed");
		return;
	}

	char * src = NULL;
	src = (char *) res;
	char * dst = src+32;

    memDump((void *)src, (void*)dst);

    newLine();
    for(int i=0; i<bufferMem; i++) {
        printf(" - %x",1, src[i]);
    }
	newLine();
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
            print("Something went wrong. ");
    }
    printf("Please, try again.\\n\\n",0);
}

/* --------------------------------------------------------------------------------------------------------------------------
                                COMMAND-CHECK METHODS
------------------------------------------------------------------------------------------------------------------------- */

static int checkEmptySpace(char * buffer, int start, int length) {

	for (int i=start; i<=length && buffer[i]; i++) {
		if (!isSpace(buffer[i]))
			return 0;
	}

	return 1;
}

static int isCommandTemp(char * buffer, int length) {
	char * str = "cputemp";

    if (!strncmp(str,buffer,7))
		return 0;

    return checkEmptySpace(buffer,7,length);
}
static int isCommandHelp(char * buffer, int length) {
	char * str = "help";
	if (!strncmp(str,buffer,4))
		return 0;

    return checkEmptySpace(buffer,4,length);
}
static int isCommandMemdump(char * buffer, int length, char * start) {
	char * aux1 = "memdata";
	if (!strncmp(aux1,buffer,7))
		return 0;

	start[0] = '0';
	start[1] = 'x';
	if(checkEmptySpace(buffer,7,length)) {
		start[2] = '0';
		start[3] = 0;
		return 1;
	}

	char * aux2 = " 0x";
	if(!strncmp(aux2,buffer+7,3)) {
		return 0;
	}

	int aux3 = 10;
	int i = 2;
	while(isHexa(*(buffer+aux3)) && aux3<length && aux3<(10+16)) {
		start[i++]=buffer[aux3++];
	}
	start[i]=0;

	return checkEmptySpace(buffer,aux3,length);
}
static int isCommandProcdata(char * buffer, int length) {
	char * str = "mpdata";
	if (!strncmp(str,buffer,6))
		return 0;

    return checkEmptySpace(buffer,6,length);
}
static int isCommandRegdata(char * buffer, int length) {
	char * str = "regdata";
	if (!strncmp(str,buffer,7))
		return 0;

    return checkEmptySpace(buffer,7,length);
}
static int isCommandTime(char * buffer, int length) {
	char * str = "time";
	if (!strncmp(str,buffer,4))
		return 0;

    return checkEmptySpace(buffer,4,length);
}


static int isAllowedChar(char c) {
    if (isAlpha(c) || isDigit(c) || isSpace(c) || c==0)
        return 1;
    return 0;
}

command setCommand(char * buffer, int length, char * string) {
    for (int i=0; i< BUFFERW2; i++) {
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

static int parseHexa(char * start) {
	int res = 0;
	if(start[0]!='0' || start[1]!='x') {
		return -1;
	}

	for(int i=2; start[i]; i++) {
		char c = '0';

		if (isDigit(start[i]))
			c='0';
		else if(isLower(start[i]))
			c = 'a';
		else
			c = 'A';
		res = res*16 + start[i] - c;
	}

	return res;
}