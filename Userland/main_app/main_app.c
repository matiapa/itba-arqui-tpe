#include <malloc.h>
#include <syscalls.h>
#include <tests.h>

void window1();
void window2();
void initWindow1();
void initWindow2();
void tests();

int main(){

	initWindow1();
	initWindow2();

	while(1){
		window1();
		window2();
	}
	
	return 1;

}