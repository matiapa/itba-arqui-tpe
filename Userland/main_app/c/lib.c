#include <keyboard_lib.h>
#include <screen_lib.h>

/* --------------------------------------------------------------------------- 
                            STRING FUNCTIONS
 --------------------------------------------------------------------------- */

void reverseStr(char str[], int length) { 
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


void itoa(int num, char *str) { 
    int i = 0; 
    int isNegative = 0; 
  
    if (num == 0) { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return;
    } 
  
    if (num<0) { 
        isNegative = 1; 
        num = -num; 
    } 
  
    while (num != 0) { 
        int rem = num % 10; 
        str[i++] = rem + '0'; 
        num = num/10; 
    } 
  
    if (isNegative==1) 
        str[i++] = '-'; 
  
    str[i] = '\0';
  
    reverseStr(str, i); 

}


/* --------------------------------------------------------------------------- 
                            HELPER FUNCTIONS
 --------------------------------------------------------------------------- */

void printKeyStrokes(){

	int pos = read();
	
	char str[10];
	itoa(pos, str);
	print("Got key: ");
	printLine(str);
	printLine("");

}