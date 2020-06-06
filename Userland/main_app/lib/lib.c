#include <keyboard_lib.h>
#include <windows_lib.h>
#include <malloc.h>
#include <stdarg.h>

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