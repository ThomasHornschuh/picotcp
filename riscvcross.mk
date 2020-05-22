.PHONY: build clean

COMPILER_PREFIX?=$(TARGET_PREFIX)-

PICO_OPTIONS?= IPFILTER=0 DHCP_SERVER=0 NAT=0 MCAST=1  \
	 		   PPP=0 IPV6=0 AODV=0 MDNS=1 TFTP=1 

build_debug:
	make CROSS_COMPILE=$(COMPILER_PREFIX)  ARCH=rv32im  PREFIX=build_rv32_debug \
	 $(PICO_OPTIONS) \
	 DEBUG=1 \
	 PLATFORM_CFLAGS=" -og -ffunction-sections -fdata-sections"

build_runtime:
	make CROSS_COMPILE=$(COMPILER_PREFIX)  ARCH=rv32im  PREFIX=build_rv32 \
	 $(PICO_OPTIONS) \
	 DEBUG=0 \
	 PLATFORM_CFLAGS=" -os -ffunction-sections -fdata-sections"


build: build_debug build_runtime

clean:
	make clean  PREFIX=build_rv32
	make clean  PREFIX=build_rv32_debug