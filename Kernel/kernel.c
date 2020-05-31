#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idt_loader.h>
#include <screen_driver.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const mainAppAddress = (void*)0x400000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize){
	memset(bssAddress, 0, bssSize);
}

void * getStackBase(){
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary(){
	void * moduleAddresses[] = {
		mainAppAddress,
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main(){

	load_idt();

	((EntryPoint) mainAppAddress)();

	for(int x=0; x<720; x++) draw(x, 100, 0xFF0000);

	int * num1 = malloc(4);
	*num1 = 4;

	for(int x=0; x<720; x++) draw(x, 200, 0xFF0000);

	int * num2 = malloc(4);
	*num2 = 8;

	for(int x=0; x<720; x++) draw(x, 300, 0xFF0000);

	if(*num1 + *num2 == 12){
		for(int x=0; x<720; x++)
			draw(x, 400, 0xFF0000);
	}
		
	return 0;
}