/*---------------------------------------------------------------------------------------------------
|   KERNEL_MESSAGES.H    |                                                                          |
|----------------------                                                                             |
| This file defines numbers that are used by the kernel to send messages to userspace apps.         |
| Also, it defines the address at which the main app of userspace is loaded.                  	    |
---------------------------------------------------------------------------------------------------*/
#define START 0
#define TIMER_TICK_INT 1
#define EXCEPTION_PRODUCED 2


static void * const mainApp = (void*)0x400000;

typedef int (*EntryPoint)(int message, int nargs, ...);