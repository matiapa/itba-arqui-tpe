#include <screen_driver.h>
#include <lib.h>
#include <kernel_messages.h>

typedef struct LastException{
	int id;
	void * eip;
} LastException;

LastException lastException;


void getLastException(LastException *exception){
	memcpy(exception, &lastException, sizeof(LastException));
}


void exceptionDispatcher(int id, void * eip) {
	lastException.id = id;
	lastException.eip = eip;

	((EntryPoint) mainApp)(EXCEPTION_PRODUCED);
}