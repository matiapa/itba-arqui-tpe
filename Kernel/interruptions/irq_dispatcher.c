#include <stdint.h>
#include <screen_driver.h>
#include <keyboard_driver.h>
#include <lib.h>

static void int_20();

static void int_21();

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:			// Timer tick
			int_20();
			break;
		case 1:			// Keyboard
			int_21();
			break;
	}
	return;
}



// RTC
void int_20() {


}


void storeState();

int x=100;

// Keyboard
void int_21() {


}
