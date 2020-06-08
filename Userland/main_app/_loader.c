/* _loader.c */
#include <stdint.h>
#include <kernel_messages.h>
#include <programs.h>

extern char bss;
extern char endOfBinary;

int main();

void * memset(void * destiny, int32_t c, uint64_t length);

int _start(int message) {
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	switch(message){
		case START:
			return main();

		case EXCEPTION_PRODUCED:
			return exception();

		case TIMER_TICK_INT:
			return interruption(TIMER_TICK_INT);

		default:
			return main();
	}

}


void * memset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}
