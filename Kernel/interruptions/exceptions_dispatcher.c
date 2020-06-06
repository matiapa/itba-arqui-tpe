#include <screen_driver.h>

#define NO_EXCEPTION -1

static void * const mainAppAddress = (void*)0x400000;
typedef int (*EntryPoint)();

int latestException = NO_EXCEPTION;


int getLatestException(){
	int aux = latestException;
	latestException = NO_EXCEPTION;
	return aux;
}


void exceptionDispatcher(int exception) {
	for(int i=0; i<1000; i++)
		draw(800, i, 0xFF0000);

	latestException = exception;
	((EntryPoint) mainAppAddress)();
}