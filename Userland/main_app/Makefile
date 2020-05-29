include ../Makefile.inc

MODULE=main_app.bin
SOURCES_C=$(wildcard c/*.c)
SOURCES_ASM=$(wildcard asm/*.s)

all: $(MODULE)

$(MODULE): $(SOURCES_C)
	$(GCC) $(GCCFLAGS) -I./include -T main_app.ld _loader.c $(SOURCES_ASM) $(SOURCES_C) -o ../$(MODULE)

clean:
	rm -rf *.o

.PHONY: all clean print
