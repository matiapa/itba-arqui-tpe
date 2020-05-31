#include <stdint.h>

// ------------------------------------------------ DRAW (1) -------------------------------------------------------------

void draw(int x, int y, int rgb);

// ------------------------------------------------ READ (2) -------------------------------------------------------------

int read();

// ------------------------------------------------ GETRES (3) -------------------------------------------------------------

typedef struct ScreenRes{
    int height, width;
} ScreenRes;


void getRes(ScreenRes * res);

// ------------------------------------------------ REGDUMP (4) -------------------------------------------------------------

typedef struct RegDump{
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, rip, r8, r9, r10, r11, r12, r13, r14, r15, eflags;
} RegDump;

void regDump(RegDump *dump);

// ------------------------------------------------ MEMDUMP (5) -------------------------------------------------------------

void memDump(void *src, void *dest);

// ------------------------------------------------ GETTIME (6) -------------------------------------------------------------

typedef struct Time{
    int hours, minutes, seconds;
} Time;

void getTime(Time * time);

// ------------------------------------------------ CPUINFO (7) -------------------------------------------------------------

typedef struct CPUInfo{
    char *brandName, *brandDesc;
} CPUInfo;

void cpuInfo(CPUInfo * info);