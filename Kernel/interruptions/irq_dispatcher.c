#include <stdint.h>
#include <screen_driver.h>
#include <keyboard_driver.h>
#include <lib.h>
#include <kernel_messages.h>

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


static int ints = 0;

// RTC
void int_20() {

	// ints += 1;

	// if(ints>0 && ints%10 == 0)
	// 	((EntryPoint) mainApp)(TIMER_TICK_INT);

	// draw(ints, 100, 0xFF0000);

}


void storeState();

int x=100;

// Keyboard
void int_21() {


}
