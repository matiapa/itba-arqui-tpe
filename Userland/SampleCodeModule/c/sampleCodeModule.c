/* sampleCodeModule.c */
#include <screen_lib.h>
#include <keyboard_lib.h>

int main(){

	while(1){
		printChar(getChar());
	}
	
	return 1;
}