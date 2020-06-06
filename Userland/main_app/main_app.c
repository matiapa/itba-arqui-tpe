#include <syscalls.h>
#include <tests.h>

void window1();
void window2();
void initWindow1();
void initWindow2();
void exception(int id);

int main(){

	int latestException = getLatestException();

	if(latestException == -1){

		initWindow1();
		initWindow2();

		while(1){
			window1();
			window2();
		}

	}else{

		exception(0);

	}
	
	return 1;

}