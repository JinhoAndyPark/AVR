###############################################################################
# Makefile for the project parking_slave
###############################################################################

## General Flags
PROJECT = parking_slave
MCU = atmega128
TARGET = parking_slave.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99     -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=parking_slave.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Libraries
LIBS = -lc -lm -lobjc 

## Objects that must be built in order to link
OBJECTS = main.o timer.o uart.o adc.o lcd_text.o motor_ax.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) parking_slave.hex parking_slave.eep parking_slave.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../AVRLIB/timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../AVRLIB/uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

adc.o: ../AVRLIB/adc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd_text.o: ../APPLIB/lcd_text.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

motor_ax.o: ../APPLIB/motor_ax.c
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
	-rm -rf $(OBJECTS) parking_slave.elf dep/* parking_slave.hex parking_slave.eep parking_slave.lss parking_slave.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

