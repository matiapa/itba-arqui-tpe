#include <stdint.h>

int isAlpha(char);

int isLower(char);

int isUpper(char);

void reverseStr(char str[], int length);

char * itoa(int num, char * str, int base);

char * dtoa(double num, char * str);

void printKeyStrokes();

void printf(char * format, int nargs, ...);

int strcmp(char * str1, char * str2);


typedef struct RegDump{
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, rip, r8, r9, r10, r11, r12, r13, r14, r15;
} RegDump;

void regDump(RegDump *dump);

