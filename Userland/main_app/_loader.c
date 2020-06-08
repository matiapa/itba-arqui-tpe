/* _loader.c */
#include <stdint.h>
#include <kernel_messages.h>
#include <programs.h>

extern char bss;
extern char endOfBinary;

int main();

void * memset(void * destiny, int32_t c, uint64_t length);

int _start(int message, int nargs, ...) {

	va_list valist;
    va_start(valist, nargs);

	switch(message){
		case START:
			return main();

		case EXCEPTION_PRODUCED:
			return exception(valist);

		case IRQ_PRODUCED:
			return interruption(valist);

		default:
			return main();
	}

}