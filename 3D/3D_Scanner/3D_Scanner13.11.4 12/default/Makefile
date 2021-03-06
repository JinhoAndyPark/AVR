###############################################################################
# Makefile for the project 3D_Scanner
###############################################################################

## General Flags
PROJECT = 3D_Scanner
MCU = atmega128
TARGET = 3D_Scanner.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=3D_Scanner.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o adc.o timer.o uart.o motor_step.o ext_interrupt.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) 3D_Scanner.hex 3D_Scanner.eep 3D_Scanner.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

adc.o: ../AVRLIB/adc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../AVRLIB/timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../AVRLIB/uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

motor_step.o: ../APPLIB/motor_step.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ext_interrupt.o: ../AVRLIB/ext_interrupt.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) 3D_Scanner.elf dep/* 3D_Scanner.hex 3D_Scanner.eep 3D_Scanner.lss 3D_Scanner.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

