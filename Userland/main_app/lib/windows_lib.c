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

const int bufferNumber = 15;

void printMPinfo(void) {
    CPUInfo * info = malloc(sizeof(CPUInfo));
    cpuInfo(info);

    print("Brand name: ");
    printLine(info->brandName);
    print("Brand description: ");
    printLine(info->brandDesc);

    /*
    printf("\nBrand name: %s", info->brandName);
    printf("\nBrand description: %s\n", info->brandDesc);
    */
    newLine();
}

void printCPUtemp(void) {
    int temp = cpuTemp();
    char * stemp = malloc(bufferNumber);
    stemp = itoa(temp,stemp,10);

    newLine();
    print("Computer's Temperature in Celcius: ");
    printLine(stemp);

    /*
    printf("\nComputer's Temperature in Celcius: %d\n\n", temp);
    */
}

void printTime(void) {
    Time * t = malloc(sizeof(Time));
    getTime(t);
    char * s = malloc(bufferNumber);

    print("Time now: ");
    print(itoa(t->hours,s,10));
    print(":");
    print(itoa(t->minutes,s,10));
    print(":");
    printLine(itoa(t->seconds,s,10));

    /*
    printf("\nTime now: %d:%d:%d\n", t->hours, t->minutes, t->seconds);
    */
}

void printRegdump() {
    RegDump * reg = malloc(sizeof(RegDump));
    regDump(reg);
    char * s = malloc(bufferNumber);

    printLine("Register's values:");
    printLine(itoa(reg->rax,s,10));
    printLine(itoa(reg->rbx,s,10));

    /*
    printf("\nRegister's values:");
    printf("\n --- --- --- --- --- --- --- --- --- --- --- --- ---");
    printf("\n - rax - %d", reg->rax);
    printf("\n - rbx - %d", reg->rbx);
    printf("\n - rcx - %d", reg->rcx);
    printf("\n - rdx - %d", reg->rdx);
    printf("\n - rsi - %d", reg->rsi);
    printf("\n - rdi - %d", reg->rdi);
    printf("\n - rbp - %d", reg->rbp);
    printf("\n - rsp - %d", reg->rsp);

    printf("\n --- --- --- --- --- --- --- --- --- --- --- --- ---");
    printf("\n - r8 - %d", reg->r8);
    printf("\n - r9 - %d", reg->r9);
    printf("\n - r10 - %d", reg->r10);
    printf("\n - r11 - %d", reg->r11);
    printf("\n - r12 - %d", reg->r12);
    printf("\n - r13 - %d", reg->r13);
    printf("\n - r14 - %d", reg->r14);
    printf("\n - r15 - %d", reg->r15);

    printf("\n --- --- --- --- --- --- --- --- --- --- --- --- ---\n");
    printf("\n - eflags - %d\n\n", reg->eflags);
    */
}

void printMemdump(int start) {

    int * src = &start;
    int aux = start + 32 * 8;
    int * dest = &aux;

    memDump(src, dest);
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

/* --------------------------------------------------------------------------------------------------------------------------
                                        CALCULATOR METHODS
------------------------------------------------------------------------------------------------------------------------- */

void calculateString(char * s) {

    double result = 324.32;
    
    print(" >> ");
    printLine(dtoa(result));

}