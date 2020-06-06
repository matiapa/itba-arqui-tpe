#include <keyboard_lib.h>
#include <windows_lib.h>
#include <malloc.h>
#include <stdarg.h>
#include <userlib.h>

#define ITOA_MAX_LEN 10
#define DTOA_FLOAT_MAX_LEN 4
#define EPSILON 0.0001

/* --------------------------------------------------------------------------- 
                            CHAR FUNCTIONS
 --------------------------------------------------------------------------- */

int isLower(char c) {
    if (c>='a' && c<='z')
        return 1;
    return 0;
}

int isUpper(char c) {
    if (c>='A' && c<='Z')
        return 1;
    return 0;
}

char toLower(char c) {
    if (isUpper(c))
        return c + 'a' - 'A';
    return c;
}

int isAlpha(char c) {
    if (isLower(c) || isUpper(c))
        return 1;
    return 0;
}

/* --------------------------------------------------------------------------- 
                            STRING FUNCTIONS
 --------------------------------------------------------------------------- */

void reverseStr(char * str, int length) { 
    int start = 0; 
    int end = length -1; 
    while (start < end) { 
        char aux = str[start];
        str[start] = str[end];
        str[end] = aux;
        start++; 
        end--; 
    } 
}

/* -----------------------------------------------------------
 Taken from https://www.geeksforgeeks.org/implement-itoa/
----------------------------------------------------------- */

char* itoa(int num, char* str, int base){     
    int i = 0;
    int isNegative = 0; 
  
    if (num == 0){ 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10){
        isNegative = 1; 
        num = -num;
    } 
  
    while (num != 0){
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0'; 
        num = num/base; 
    } 
  
    if (isNegative == 1) 
        str[i++] = '-'; 
  
    str[i] = '\0';
  
    reverseStr(str, i); 
  
    return str; 
}

char * dtoa(double num) {

    char * str = (char *) malloc(ITOA_MAX_LEN+DTOA_FLOAT_MAX_LEN);
    int i = 0;

    if (num < EPSILON && num > -EPSILON) { 
        str[i++] = '0';
        str[i++] = '.';
        str[i++] = '0';

        str[i] = '\0'; 
        return str; 
    } 
  
    int auxNum = (int) num;
    // --- Building the int part ---
    while (auxNum > EPSILON) { 
        int rem = auxNum % 10; 
        str[i++] = rem + '0'; 
        auxNum = auxNum/10; 
    } 

    int isNegative = 0;
    if (num < 0){
        isNegative = 1; 
        num = -num;
    } 
    if (isNegative == 1) 
        str[i++] = '-'; 
  
    reverseStr(str, i); 
    str[i++] = '.'; 

    for (int j=0; j<DTOA_FLOAT_MAX_LEN; j++) {
        num = num*10;
        int aux = (int) num;
        str[i++] = aux%10 + '0';
    }
   
    str[i] = '\0';
    return str;

}

/* -----------------------------------------------------------
    Bare printf, only supports dec and hex nums as formats
-------------------------------------------------------------- */
void printf(char *format, int nargs, ...){

    va_list valist;

    va_start(valist, nargs);

    int pos, formatChar=0, specialChar=0;
    for(pos=0; format[pos]!=0; pos++){

        if(format[pos] == '%'){
            formatChar = 1;
            continue;
        }

        if(formatChar == 1){

            formatChar = 0;

            if(format[pos] == 'd'){
                char *str = malloc(20);
                print(itoa(va_arg(valist, int), str, 10));
                continue;
            }

            if(format[pos] == 'x'){
                char *str = malloc(20);
                print("0x");
                print(itoa(va_arg(valist, int), str, 16));
                continue;
            }

        }

        if(format[pos] == '\\'){
            specialChar = 1;
            continue;
        }

        if(specialChar == 1){

            specialChar = 0;

            if(format[pos] == 'n'){
                printLine("");
                continue;
            }

        }

        printChar(format[pos]);

    }

    va_end(valist);


}

/* --------------------------------------------------------------------------- 
                            HELPER FUNCTIONS
 --------------------------------------------------------------------------- */

void printKeyStrokes(){

	int pos = read();
	print("Got key: ");

    char * str = (char *) malloc(20);
	printLine(itoa(pos, str, 10));

	printLine("");
}