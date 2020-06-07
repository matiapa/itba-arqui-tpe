#include <stdint.h>

int isAlpha(char);

int isDigit(char);

int isHexa(char);

int isDecimalPoint(char);

int isSpace(char);

int isLower(char);

int isUpper(char);

char toLower(char);

void reverseStr(char str[], int length);

char * itoa(int num, char * str, int base);

char * dtoa(double num, char * str);

void printKeyStrokes();

void printf(char * format, int nargs, ...);

int strcmp(char * str1, char * str2);

int strncmp(char * s1, char * s2, int length);

typedef struct RegDump{
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, rip, r8, r9, r10, r11, r12, r13, r14, r15;
} RegDump;

void regDump(RegDump *dump);

