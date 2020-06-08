/*---------------------------------------------------------------------------------------------------
|   EXCEPTION_WINDOW.C    |                                                                         |
|----------------------                                                                             |
| This windows display exception information when they are produced. This includes common registers |
|  at the moment of the exception, and which was the exception produced.					        |
---------------------------------------------------------------------------------------------------*/

#include <programs.h>
#include <windows_lib.h>
#include <std_lib.h>
#include <syscalls.h>
#include <keyboard_lib.h>
#include <kernel_messages.h>

/* --------------------------------------------------------------------------------------------------------------------------
                                        		DEFINITIONS
------------------------------------------------------------------------------------------------------------------------- */

#define cursor 0

static Window w;


/* --------------------------------------------------------------------------------------------------------------------------
                                        		METHODS
------------------------------------------------------------------------------------------------------------------------- */


static void createWindow(){

	ScreenRes res;
	getRes(&res);

	w.xi = 0; w.xf = res.width;
    w.yi = 0; w.yf = res.height;

    w.textBackground = 0x0000FF;

	w.cursors[cursor].x=0;	w.cursors[cursor].y=0;
	w.cursors[cursor].fontColor=0xFFFFFF;	w.cursors[cursor].fontSize=2;

    setWindow(&w);

}


int exception(va_list args){

    int id = va_arg(args, int);
    void * eip = va_arg(args, void *);

    createWindow();
	w.activeCursor = cursor;

    for(int x=0; x<w.xf-w.xi; x++){
        for(int y=0; y<w.yf-w.yi; y++){
            draw(x, y, 0x0000FF);
        }
    }

    switch(id){
        case 0:
            printf("Division by zero detected! Return to elementary school and press enter to restart the system\\n", 0);
            break;
        case 6:
            printf("Invalid opcode detected! Trying to destroy the machine? Received an EMP attack? Press enter to restart the system\\n", 0);
            break;
    }

    RegBkp bkp;
    getRegBkp(&bkp);

    printf("\\nFeed this information to the developers", 0);
    printf("\\nRAX: %x - RBX: %x - RCX: %x - RDX: %x", 4, bkp.rax, bkp.rbx, bkp.rcx, bkp.rcx);
    printf("\\nRIP: %x - RBP: %x - RSI: %x - RDI: %x", 4, eip, bkp.rbp, bkp.rsi, bkp.rdi);

    while(1){
        if(getChar()==13){
            for(int x=w.xi; x<w.xf; x++){
                for(int y=w.yi; y<w.yf; y++){
                    draw(x, y, 0x000000);
                }
            }
            main(START);
        }
    }

    return 1;
    
}