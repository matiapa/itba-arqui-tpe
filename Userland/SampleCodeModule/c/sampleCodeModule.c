/* sampleCodeModule.c */
#include <screen_lib.h>
#include <keyboard_lib.h>

int main(){

	//while(1);

	for(int x=0; x<720; x++)
		draw(x, 200, 0x00FF00);

	while(1){
		printChar(getChar());
	}
	
	//print("ABC");

	return 1;
}