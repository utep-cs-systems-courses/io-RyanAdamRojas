# Makefile configuration
COMMON_OBJECTS = main.o timeAdvStateMachines.o
CPU = msp430g2553
CFLAGS = -mmcu=${CPU} -I../h
LDFLAGS = -L/opt/ti/msp430_gcc/include

# Compiler and assembler definitions
CC = msp430-elf-gcc
AS = msp430-elf-as

# Targets for both C and assembly versions
all: led-c.elf led-s.elf

# Compile C files into object files
main.o: main.c led.h
	$(CC) $(CFLAGS) -c -o $@ $<

timeAdvStateMachines.o: timeAdvStateMachines-c.c led.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Add other object file rules here if needed

# Link object files into the final C ELF binary
led-c.elf: $(COMMON_OBJECTS) blinkUpdate.o secondUpdate.o oncePerSecond.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ ../lib/libTimer.a

# Compile assembly files into object files
greenControl-s.o: greenControl-s.s
	$(AS) -o $@ $<

blinkUpdate-s.o: blinkUpdate-s.s
	$(AS) -o $@ $<

oncePerSecond-s.o: oncePerSecond-s.s
	$(AS) -o $@ $<

secondUpdate-s.o: secondUpdate-s.s
	$(AS) -o $@ $<

timeAdvStateMachines-s.o: timeAdvStateMachines-s.s
	$(AS) -o $@ $<

# Link object files from assembly into the final S ELF binary
led-s.elf: $(COMMON_OBJECTS:.o=-s.o)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ ../lib/libTimer.a

# Loaders for the ELF binaries
load-c: led-c.elf
	msp430loader.sh $^

load-s: led-s.elf
	msp430loader.sh $^

# Clean the build directory
clean:
	rm -f *.o *.elf

# Object file dependencies
blinkUpdate.o: blinkUpdate-c.c blinkUpdate.h
	$(CC) $(CFLAGS) -c -o $@ $<

secondUpdate.o: secondUpdate-c.c secondUpdate.h
	$(CC) $(CFLAGS) -c -o $@ $<

oncePerSecond.o: oncePerSecond-c.c oncePerSecond.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Add more dependencies as needed
