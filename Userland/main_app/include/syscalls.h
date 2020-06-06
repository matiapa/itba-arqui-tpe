#include <stdint.h>

// ------------------------------------------------ DRAW (1) -------------------------------------------------------------

int draw(int x, int y, int rgb);

// ------------------------------------------------ READ (2) -------------------------------------------------------------

int read();

// ------------------------------------------------ GETRES (3) -------------------------------------------------------------

typedef struct ScreenRes{
    int height, width;
} ScreenRes;


void getRes(ScreenRes * res);

// ------------------------------------------------ MEMDUMP (4) -------------------------------------------------------------

void memDump(void *src, void *dest);

// ------------------------------------------------ GETTIME (5) -------------------------------------------------------------

typedef struct Time{
    int hours, minutes, seconds;
} Time;

void getTime(Time * time);

// ------------------------------------------------ CPUINFO (6) -------------------------------------------------------------

typedef struct CPUInfo{
    char *brandName, *brandDesc;
} CPUInfo;

void cpuInfo(CPUInfo * info);

// ------------------------------------------------ CPUTEMP (7) -------------------------------------------------------------

int cpuTemp();

// ------------------------------------- GETLATESTEXCEPTION (8) -------------------------------------------------------------

typedef struct LastException{
	int id;
	int handled;
	void * eip;
} LastException;

void getLastException(LastException *LastException);