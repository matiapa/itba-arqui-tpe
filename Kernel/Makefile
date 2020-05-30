include Makefile.inc

# For c directory

SOURCES_C=$(wildcard c/*.c)		# Grabs all .c files

# For asm directory

SOURCES_ASM=$(wildcard asm/*.s)	# Grabs all .asm files

# For asm_own directory
# This folder has been created for own assemblys, since for some reason Pure64 executes files on the asm folder during load

SOURCES_ASM_OWN=$(wildcard asm_own/*.s)	# Grabs all .asm files

KERNEL=kernel.bin

STATICLIBS=

all: $(KERNEL)		# Default rule, requisite is kernel rule

$(KERNEL): $(SOURCES_ASM) $(SOURCES_ASM_OWN) $(SOURCES_C) $(STATICLIBS)	# All .o's are requisite
	$(GCC) $(GCCFLAGS) -I./include -T kernel.ld -o $(KERNEL) $(SOURCES_ASM) $(SOURCES_ASM_OWN) $(SOURCES_C) $(STATICLIBS)

# %.o: %.c		# Matches all .c requisites and use as target a .o with the same name
# 	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

# %.o : %.asm		# Matches all .asm requisites and use as target a .o with the same name
# 	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o asm_own/*.o c/*.o *.bin

.PHONY: all clean
