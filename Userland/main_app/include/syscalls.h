void draw(int x, int y, int rgb);

int read();

// ------------------------------------------------------------------------------------------------------------------------

typedef struct ScreenRes{
    int height;
    int width;
} ScreenRes;


ScreenRes * getRes();

// ------------------------------------------------------------------------------------------------------------------------

void * regDump();

void memDump(void *src, void *dest);

void * getTime();

void * cpuInfo();

double cpuTemp();