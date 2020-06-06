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

int main(){

	LastException lastException;
	getLastException(&lastException);

	if(lastException.handled == 1){

		initWindow1();
		initWindow2();

		while(1){
			window1();
			window2();
		}

	}else{

		exception(lastException);

	}
	
	return 1;

}