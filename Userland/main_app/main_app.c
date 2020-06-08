/*---------------------------------------------------------------------------------------------------
|   MAIN_APP.C    |                                                                              	|
|----------------------                                                                             |
| This app will alternate between two windows, starting with the first one. Also, since it is the  	|
| app start point, it will check if an exception was produced before, and if so, display the		|
| exceptions screen.                                  				        						|
---------------------------------------------------------------------------------------------------*/

#include <syscalls.h>
#include <tests.h>
#include <windows.h>
#include <kernel_messages.h>

int main(int message){

	if(message == START){

		initWindow1();
		initWindow2();

		while(1){
			window1();
			window2();
		}

	}
	
	if(message == EXCEPTION_PRODUCED){

		exception();

	}
	
	return 1;

}