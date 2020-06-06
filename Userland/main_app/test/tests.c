#include <windows_lib.h>
#include <userlib.h>
#include <syscalls.h>

#define bodyCursor 0

static Window w;

static void createWindow(){

	ScreenRes res;
	getRes(&res);

	w.xi = 0; w.xf = res.width;
    w.yi = 0; w.yf = res.height;

	w.cursors[bodyCursor].x=0;	w.cursors[bodyCursor].y=0;
	w.cursors[bodyCursor].fontColor=0xFFFFFF;	w.cursors[bodyCursor].fontSize=2;

    setWindow(&w);

}


void testRegDump();
void regDumpTestSet();
void testMemDump();
void testGetTime();
void testCPUTemp();
void testCPUInfo();

void testInvalidOpcode();
int testDivByZero(int n);


void test(){

    createWindow();
	w.activeCursor = bodyCursor;

    //testDivByZero(0);
    //testInvalidOpcode();

    testRegDump();
    testMemDump();
    testGetTime();
    testCPUTemp();
    testCPUInfo();

    while(1);

}


/* --------------------------------------------------------------------
   Test that all registers are dumped correctly
-------------------------------------------------------------------- */

void testRegDump(){

    printf("RegDump test\\n", 0);


    // ------------ RIP -------------------

    RegDump dump;
    RegDump dump2;
    RegDump dump3;

    regDump(&dump);
    regDump(&dump2);
    __asm("nop");
    regDump(&dump3);
    
    int sizeOfRegDump = dump2.rip - dump.rip;
    if(dump3.rip - dump2.rip == sizeOfRegDump + 1)
        printf("- RIP passed\\n", 0);
    else
        printf("- RIP failed\\n", 0);


    // ------------ RBP/RSP -------------------

    regDump(&dump);
    __asm("push 1");
    regDump(&dump2);
    __asm("pop %rax");

    if(dump.rsp - dump2.rsp == 8 && dump.rbp == dump2.rbp)
        printf("- RSP/RBP passed\\n", 0);
    else
        printf("- RSP/RBP failed\\n", 0);


    // ------------- GPR ------------------
    
    regDumpTestSet();
    regDump(&dump);

    if(dump.rbx==2 && dump.rcx==3 && dump.rdx==4)
        printf("- GPR passed\\n", 0);
    else
        printf("- GPR failed\\n", 0);
   

}


void testMemDump(){

    // Reserve 33 bytes and differ the last one
    char ptr[33], ptrDmp[33];
	ptrDmp[32] = ptr[32]+1;

    // Do a dump of 32 bytes
	memDump(ptr, ptrDmp);
	
    // Check that exactly 32 bytes are equal between addresses
	int i;
	for(i=0; ptr[i]==ptrDmp[i]; i++);
    if(i==32)
        printf("\\nMemDump test passed\\n", 0);
    else
        printf("\\nMemDump test failed\\n", 0);

}


void testGetTime(){

    Time time;
	getTime(&time);

    if(time.hours>=0 && time.hours<=23 && time.minutes>=0 && time.minutes<=59 && time.seconds>=0 && time.seconds<=60)
        printf("\\nGetTime test passed\\n", 0);
    else
        printf("\\nGetTime test failed\\n", 0);

}


void testCPUInfo(){

    CPUInfo info;

    char brandName[50], brandDesc[70];
	info.brandName = (char *) &brandName;
    info.brandDesc = (char *) &brandDesc;

    cpuInfo(&info);

    if(strcmp(info.brandName, "QEMU Virtual CPU version 2.5+") == 1 && strcmp(info.brandDesc, "This processor does not support the brand identification feature") == 1)
        printf("\\nCPUInfo test passed\\n", 0);
    else
        printf("\\nCPUInfo test failed\\n", 0);

}


void testCPUTemp(){
    
    int temp = cpuTemp();

    if(temp>24)
        printf("\\nCPUTemp test passed\\n", 0);
    else
        printf("\\nCPUTemp test failed\\n", 0);

}


void invalidOpcode();

void testInvalidOpcode(){

    invalidOpcode();

}


// The argument n was placed to avoid compiler warning of div by zero

int testDivByZero(int n){

    return 2/n;

}