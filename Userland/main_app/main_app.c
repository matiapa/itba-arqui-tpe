#include <syscalls.h>
#include <tests.h>

void window1();
void window2();
void initWindow1();
void initWindow2();
void exception(LastException LastException);

int main(){

	LastException lastException;
	getLastException(&lastException);

	if(lastException.handled == 1){

		test();

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