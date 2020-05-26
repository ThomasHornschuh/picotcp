
.PHONY: all clean

PLATFORM?=ARTY_AXI
ARCH=rv32im
ABI=ilp32
DEBUGFLAG?=NODEBUG

UPLOAD_DIR?=~/upload

TARGET_PREFIX ?= riscv32-unknown-elf
TARGET_CC := $(TARGET_PREFIX)-gcc
TARGET_LD := $(TARGET_PREFIX)-gcc
TARGET_SIZE := $(TARGET_PREFIX)-size
TARGET_OBJCOPY := $(TARGET_PREFIX)-objcopy
HEXDUMP ?= hexdump

PLATFORMDIR=$(HOME)/development/bonfire/bonfire-software/platform
PICODIR=../build_rv32

#LINKDEF?=wildfboot.ld
LINKDEF_DRAM=bonfire_dram.ld
LINKDEF?=$(PLATFORMDIR)/$(PLATFORM)/firmware.ld
BOOTLINK=wildfboot.ld

TARGET_CFLAGS +=  -march=$(ARCH) -mabi=$(ABI) -Wall -Og -g  -fomit-frame-pointer -fno-inline-functions-called-once  \
	-ffreestanding -fno-builtin  -mstrict-align \
	-Wall -Werror=implicit-function-declaration \
	-DBONFIRE -D$(PLATFORM) -D$(DEBUGFLAG) -I$(PLATFORMDIR) -I$(PLATFORMDIR)/$(PLATFORM)  \
    -I$(PICODIR)/include -I$(PICODIR)/include/arch -DRISCV32


TARGET_LDFLAGS_SYSCALL += -march=$(ARCH) -mabi=$(ABI)   \
	 -Wl,--gc-sections  -Wl,-T$(LINKDEF_DRAM) 




all: build/pvtest.bin

clean:
	rm build/*
	

build/%.o : %.S
	$(TARGET_CC) $(TARGET_CFLAGS) -c $< -o $@

build/%.o : %.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c $< -o $@


build/%.bin : build/%.elf
		$(TARGET_OBJCOPY) -S -O binary $<  $@
		cp $@ $(UPLOAD_DIR)
		$(TARGET_PREFIX)-objdump -S -d $< >$(basename $@).lst
		$(TARGET_PREFIX)-objdump -s $< >$(basename $@).dmp
		$(TARGET_PREFIX)-size  $<

build/%.hex : build/%.elf
	$(TARGET_OBJCOPY) -S -O $< $(basename $@).bin
	$(HEXDUMP) -v -e '1/4 "%08x\n"' $(basename $@).bin >$@
	$(TARGET_PREFIX)-objdump -S -d $< >$(basename $@).lst
	$(TARGET_PREFIX)-objdump -s $< >$(basename $@).dmp
	$(TARGET_PREFIX)-size  $<




build/pvtest.elf :  build/main.o  build/sys.o  build/xil_etherlite.o build/ethernet_driver.o build/tcpecho.o
	$(TARGET_LD)  -o $@ $(TARGET_LDFLAGS_SYSCALL)  $^ -L$(PICODIR)/lib -lpicotcp   -lg -lm -lgloss

