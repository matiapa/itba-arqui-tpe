#include <lib.h>
#include <kernel_messages.h>

void exceptionDispatcher(int id, void * eip) {

	((EntryPoint) mainApp)(EXCEPTION_PRODUCED, 2, id, eip);

}