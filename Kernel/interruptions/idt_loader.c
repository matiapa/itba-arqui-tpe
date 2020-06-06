#include <stdint.h>
#include <defs.h>
#include <interrupts.h>
#include <syscall_handler.h>

#pragma pack(push)
#pragma pack (1)

typedef struct {
 uint16_t offset_l;
 uint16_t selector;
 uint8_t cero;
 uint8_t access;
 uint16_t offset_m;
 uint32_t offset_h;
 uint32_t other_cero;
} DESCR_INT;

#pragma pack(pop)

DESCR_INT * idt = (DESCR_INT *) 0;

void setup_IDT_entry (int index, uint64_t offset) {
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].selector = 0x08;
    idt[index].cero = 0;
    idt[index].access = ACS_INT;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
    idt[index].other_cero = 0;
}


void load_idt() {
    _cli();

    setup_IDT_entry(0, (uint64_t) &_exception0Handler);
    setup_IDT_entry(6, (uint64_t) &_exception6Handler);

    setup_IDT_entry(0x80, (uint64_t) &_syscallDispatcher);
    
    //setup_IDT_entry(0x20, (uint64_t) &_irq00Handler);
    setup_IDT_entry(0x21, (uint64_t) &_irq01Handler);
    
    picMasterMask(0xFd);

    picSlaveMask(0xFF);
    _sti();
} 

/*
None    0xFF    1111 1111
Timer   0xFE    1111 1110
Keybrd  0xFD    1111 1101
*/