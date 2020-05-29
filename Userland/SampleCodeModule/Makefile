include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

SOURCES_C=$(wildcard c/*.c)
OBJECTS_C=$(SOURCES_C:.c=.o)

SOURCES_ASM=$(wildcard asm_own/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_C) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(OBJECTS_ASM) $(OBJECTS_C)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm_own/*.o c/*.o

.PHONY: all clean print