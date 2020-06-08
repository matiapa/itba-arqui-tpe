/*---------------------------------------------------------------------------------------------------
|   MAIN_APP.C    |                                                                              	|
|----------------------                                                                             |
| This app will alternate between two windows, starting with the first one. Also, since it is the  	|
| app start point, it will check if an exception was produced before, and if so, display the		|
| exceptions screen.                                  				        						|
---------------------------------------------------------------------------------------------------*/

#include <programs.h>
#include <syscalls.h>
#include <windows.h>
#include <kernel_messages.h>

int main(){

	initWindow1();
	initWindow2();

	while(1){
		window1();
		window2();
	}
	
	return 1;

}