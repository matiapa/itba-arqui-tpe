/* sampleCodeModule.c */
#include <screen_lib.h>

int main(){

	//while(1);

	for(int x=0; x<720; x++)
		draw(x, 200, 0x00FF00);

	return 1;
}