#include <screen_driver.h>
#include <lib.h>

typedef struct LastException{
	int id;
	int handled;
	void * eip;
} LastException;

LastException lastException = {0, 1, (void *) 0};

static void * const mainAppAddress = (void*)0x400000;
typedef int (*EntryPoint)();


void getLastException(LastException *exception){
	memcpy(exception, &lastException, sizeof(LastException));
	lastException.handled = 1;
}


void exceptionDispatcher(int id, void * eip) {
	lastException.handled = 0;
	lastException.id = id;
	lastException.eip = eip;

	((EntryPoint) mainAppAddress)();
}