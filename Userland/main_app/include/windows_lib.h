#include <syscalls.h>

struct ScreenRes * getRes();

typedef struct Cursor{
    int x, y;

    int fontSize, fontColor;
} Cursor;


typedef struct Window{
    int xi, xf, yi, yf;
    
    Cursor cursors[3];
    int activeCursor;
    
} Window;


void setWindow(Window *window);


void drawPoint(int x, int y, int size, int rgb);

void drawChar(int x, int y, char c, int size, int rgb);


void clearScreen();

void printChar(char c);

void print(char c[]);

void printLine(char c[]);