include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES_C=$(wildcard c/*.c)
SOURCES_ASM=$(wildcard asm_own/*.s)

all: $(MODULE)

$(MODULE): $(SOURCES_C)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld _loader.c $(SOURCES_ASM) $(SOURCES_C) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print
