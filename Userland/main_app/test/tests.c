#include <windows_lib.h>
#include <malloc.h>
#include <userlib.h>
#include <syscalls.h>

#define bodyCursor 0

Window *w;

static void createWindow(){

	w = (Window *) malloc(sizeof(Window));

	ScreenRes * res = (ScreenRes *) malloc(sizeof(ScreenRes));
	getRes(res);

	w->xi = 0; w->xf = res->width;
    w->yi = 0; w->yf = res->height;

	w->cursors[bodyCursor].x=0;	w->cursors[bodyCursor].y=0;
	w->cursors[bodyCursor].fontColor=0xFFFFFF;	w->cursors[bodyCursor].fontSize=2;

    setWindow(w);

}


void testRegDump();
void regDumpTestSet();
void testMemDump();


void test(){

    createWindow();
	w->activeCursor = bodyCursor;

    printf("Dest: %d", 9);
    //testRegDump();
    //testMemDump();

    while(1);

}


/* --------------------------------------------------------------------
   Test that all registers are dumped correctly
-------------------------------------------------------------------- */

void testRegDump(){

    printf("RegDump test\\n", 0);


    // ------------ RIP -------------------

    RegDump * dump = malloc(sizeof(RegDump));
    RegDump * dump2 = malloc(sizeof(RegDump));
    RegDump * dump3 = malloc(sizeof(RegDump));

    regDump(dump);
    regDump(dump2);
    __asm("nop");
    regDump(dump3);
    
    int sizeOfRegDump = dump2->rip - dump->rip;
    if(dump3->rip - dump2->rip == sizeOfRegDump + 1)
        printf("RIP passed\\n", 0);
    else
        printf("RIP failed\\n", 0);


    // ------------ RBP/RSP -------------------

    dump = malloc(sizeof(RegDump));
    dump2 = malloc(sizeof(RegDump));

    regDump(dump);
    __asm("push 1");
    regDump(dump2);
    __asm("pop %rax");

    if(dump->rsp - dump2->rsp == 8 && dump->rbp == dump2->rbp)
        printf("RSP/RBP passed\\n", 0);
    else
        printf("RSP/RBP failed\\n", 0);


    // ------------- GPR ------------------
    
    regDumpTestSet();
    regDump(dump);

    if(dump->rbx==2 && dump->rcx==3 && dump->rdx==4)
        printf("GPR passed\\n", 0);
    else
        printf("GPR failed\\n", 0);
   

}


void testMemDump(){

    // Reserve 33 bytes and differ the last one
    char *ptr = (char *) malloc(33);
	char *ptrDmp = (char *) malloc(33);
	ptrDmp[32] = ptr[32]+1;


    // Do a dump of 32 bytes
	int res = memDump(ptr, ptrDmp);
	
    // Check that exactly 32 bytes are equal between addresses
	int i;
	for(i=0; ptr[i]==ptrDmp[i]; i++);
    if(i==32)
        printf("\\nMemDump test passed\\n", 0);
    else
        printf("\\nMemDump test failed\\n", 0);

}


// void testGetTime(){

//     Time * time = malloc(sizeof(Time));
// 	getTime(time);

// 	printLine(itoa(time->hours));
// 	printLine(itoa(time->minutes));
// 	printLine(itoa(time->seconds));

// }


// void testCPUInfo(){

//     CPUInfo *info = malloc(sizeof(CPUInfo));
// 	info->brandName = malloc(50);
// 	info->brandDesc = malloc(70);
	
// 	cpuInfo(info);
// 	printLine(info->brandName);
// 	printLine(info->brandDesc);

// }


// void testRegDump(){
//     // RegDump * dump = malloc(sizeof(RegDump));
// 	// regDump(dump);
	
// 	// printLine(itoa(dump->rax));
// 	// printLine(itoa(dump->rbx));
// 	// printLine(itoa(dump->rcx));
// }


// void testCPUTemp(){
    // printLine(itoa(cpuTemp()));
// }