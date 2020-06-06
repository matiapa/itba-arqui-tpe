#include <windows_lib.h>
#include <userlib.h>
#include <syscalls.h>
#include <keyboard_lib.h>
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

void main();

void exception(int id){

    createWindow();
	w.activeCursor = bodyCursor;

    for(int x=0; x<w.xf-w.xi; x++){
        for(int y=0; y<w.yf-w.yi; y++){
            draw(x, y, 0x0000FF);
        }
    }

    if(id==0){
            printf("Division by zero detected! Return to elementary school and press enter to continue\\n", 0);
    }

    RegDump dump;
    regDump(&dump);

    printf("\\nRAX: %x - RBX: %x - RCX: %x - RDX: %x", 4, dump.rax, dump.rbx, dump.rcx, dump.rcx);
    printf("\\nRSP: %x - RBP: %x - RSI: %x - RDI: %x", 4, dump.rsp, dump.rbp, dump.rsi, dump.rdi);
    printf("\\nRIP: %x", 1, dump.rip);

    while(1){
        if(getChar()==13){
            main();
        }
    }

}