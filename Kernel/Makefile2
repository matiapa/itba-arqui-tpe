include Makefile.inc

# For c directory

SOURCES_C=$(wildcard c/*.c)		# Grabs all .c files
OBJECTS_C=$(SOURCES_C:.c=.o)	# Maps .c to .o

# For asm directory

SOURCES_ASM=$(wildcard asm/*.asm)	# Grabs all .asm files
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)	# Maps .asm to .o

# For asm_own directory
# This folder has been created for own assemblys, since for some reason Pure64 executes files on the asm folder during load

SOURCES_ASM_OWN=$(wildcard asm_own/*.asm)	# Grabs all .asm files
OBJECTS_ASM_OWN=$(SOURCES_ASM_OWN:.asm=.o)	# Maps .asm to .o

KERNEL=kernel.bin

STATICLIBS=

all: $(KERNEL)		# Default rule, requisite is kernel rule

$(KERNEL): $(OBJECTS_ASM) $(OBJECTS_ASM_OWN) $(OBJECTS_C) $(STATICLIBS)	# All .o's are requisite
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(OBJECTS_ASM) $(OBJECTS_ASM_OWN) $(OBJECTS_C) $(STATICLIBS)

%.o: %.c		# Matches all .c requisites and use as target a .o with the same name
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@
	#objcopy --only-keep-debug $@ "/home/matiapa/Arqui/TPE/DebugInfo/"$(@:.o=.sym)

%.o : %.asm		# Matches all .asm requisites and use as target a .o with the same name
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o asm_own/*.o c/*.o *.bin

.PHONY: all clean
