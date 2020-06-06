#include <windows_lib.h>
#include <userlib.h>
#include <font.h>
#include <malloc.h>
#include <syscalls.h>

const int HEIGHT = 1920;
const int WIDTH = 780;


/* --------------------------------------------------------------------------------------------------------------------------
                                            WINDOWS METHODS
-------------------------------------------------------------------------------------------------------------------------- */

Window *window;


void setWindow(Window *currWindow){
    window=currWindow;
}


// Cursor * cursor(){
//     return &(window->cursors[window->activeCursor]);
// }

#define cursor window->cursors[window->activeCursor]

#define height window->yf-window->yi

#define width window->xf-window->xi


/* --------------------------------------------------------------------------------------------------------------------------
                                            DRAW METHODS
-------------------------------------------------------------------------------------------------------------------------- */

void draw(int x, int y, int rgb);


void drawPoint(int x, int y, int size, int rgb){

    int absx = window->xi + x;
    int absy = window->yi + y;

    for(int x=absx; x<absx+size; x++){
        for(int y=absy; y<absy+size; y++){
            draw(x, y, rgb);
        }
    }

}


void drawChar(int x, int y, char c, int size, int rgb) {

    for (int col=0; col<8; col++) {
        for (int row=0; row<8; row++) {
            if(font8x8_basic[(int) c][col] & 1 << row){
                drawPoint(x+row*size, y+col*size, size, rgb);
            }
        }
    }

}


/* --------------------------------------------------------------------------------------------------------------------------
                                            TEXT METHODS
-------------------------------------------------------------------------------------------------------------------------- */

const int fontWidth = 8;
const int fontHeight = 8;
 
int charSpacing = 1;
int lineSpacing = 1;


void clearScreen(){

    for(int x=window->xi; x<window->xf; x++){
        for(int y=window->yi; y<window->yf; y++){
            draw(x, y, 0);
        }
    }

}


void nextChar(){

    cursor.x += cursor.fontSize*fontWidth+charSpacing;

    if(cursor.x > width){
        cursor.x = 0;
        cursor.y += cursor.fontSize*fontHeight+lineSpacing;
    }

    if(cursor.y > height){
        cursor.y = 0;
        clearScreen();
    }

}


void prevChar(){

    cursor.x -= cursor.fontSize*fontWidth+charSpacing;

    if(cursor.x < 0){
        cursor.x = 0;
    }

}


void newLine(){

    cursor.x = 0;
    cursor.y += cursor.fontSize*fontWidth+lineSpacing;

}


void printChar(char c){

    // Carriage return
    if(c==13){
        newLine();
        return;
    }

    // Backspace
    if(c==8){
        prevChar();
        drawPoint(cursor.x, cursor.y, cursor.fontSize*fontHeight, 0);
        return;
    }

    // Not printable
    if(c<32 || c>127)
        return;

    drawChar(cursor.x, cursor.y, c, cursor.fontSize, cursor.fontColor);

    nextChar();

}


void print(char s[]){

    for(int i=0; s[i]!=0; i++)
        printChar(s[i]);

}


void printLine(char s[]){
	
    print(s);
    newLine();

}

/* --------------------------------------------------------------------------------------------------------------------------
                                        SHELL METHODS
------------------------------------------------------------------------------------------------------------------------- */
const int bufferText = 70;
const int bufferMem = 33;

void printMPinfo(void) {
    CPUInfo * info = malloc(sizeof(CPUInfo));
    info->brandName = malloc(bufferText);
    info->brandDesc = malloc(bufferText);
    cpuInfo(info);

    printf("\\nBrand name: %s", 1, info->brandName);
    printf("\\nBrand description: %s\\n", 1, info->brandDesc);
}

void printCPUtemp(void) {
    int temp = cpuTemp();
    printf("\\n Computer's Temperature in Celcius: %d\\n", 1, temp);
}

void printTime(void) {
    Time * t = malloc(sizeof(Time));
    getTime(t);

    printf("\\nTime now: %d:%d:%d\\n", 3, t->hours, t->minutes, t->seconds);
}

void printRegdump() {
    RegDump * reg = malloc(sizeof(RegDump));
    regDump(reg);

    printLine("Register's values:");
    printLine("--- --- --- --- --- --- --- --- --- --- --- --- ---");
    printf("\\n - rax - %x", 1, reg->rax);
    printf("\\n - rbx - %x", 1, reg->rbx);
    printf("\\n - rcx - %x", 1, reg->rcx);
    printf("\\n - rdx - %x", 1, reg->rdx);
    printf("\\n - rsi - %x", 1, reg->rsi);
    printf("\\n - rdi - %x", 1, reg->rdi);
    printf("\\n - rbp - %x", 1, reg->rbp);
    printf("\\n - rsp - %x\\n", 1, reg->rsp);

    printf("\\n - r8 - %x", 1, reg->r8);
    printf("\\n - r9 - %x", 1, reg->r9);
    printf("\\n - r10 - %x", 1, reg->r10);
    printf("\\n - r11 - %x", 1, reg->r11);
    printf("\\n - r12 - %x", 1, reg->r12);
    printf("\\n - r13 - %x", 1, reg->r13);
    printf("\\n - r14 - %x", 1, reg->r14);
    printf("\\n - r15 - %x\\n", 1, reg->r15);

    printLine("--- --- --- --- --- --- --- --- --- --- --- --- ---");
}

void printMemdump(char * start) {   //TODO
    char * src = (char *) malloc(bufferMem);
    char * dest = (char *) malloc(bufferMem);
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

static int isCommandTemp(char * buffer, int length) {
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

command setCommand(char * buffer, int length, char * string) {

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
/* --------------------------------------------------------------------------------------------------------------------------
                                        CALCULATOR METHODS
------------------------------------------------------------------------------------------------------------------------- */

void calculateString(char * s) {

    double result = 324.32;
    
    print(" >> ");
    printLine(dtoa(result));

}

/* --------------------------------------------------------------------------------------------------------------------------
                                        WARNING MESSAGES
------------------------------------------------------------------------------------------------------------------------- */


void printWarning(int num) {
    printf("\\n >> Error: ", 0);
    switch(num) {
        case 0:    
            printLine("Command not found");
            printLine("If you want to see the command manual type 'help'.");
        break;
        case 1: 
            print("Zero division is not allowed.");
        break;
        case 2: 
            print("To calculate use only numbers or the following operators: ");
            printLine("+ - * / ( ) , . =");
        break;
        default: 
            print("Something went wong. ");
    }
    printf("Please, try again.\\n\\n",0);
}