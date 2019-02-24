.PHONY: build clean

build:
	make CROSS_COMPILE=riscv64-unknown-elf-  ARCH=rv32im  PREFIX=build_rv32 \
	 IPFILTER=0 DHCP_SERVER=0 NAT=0 MCAST=0 MDNS=0 \
	 PPP=0 IPV6=0 AODV=0 MDNS=0 \
	 PLATFORM_CFLAGS=" -Os -ffunction-sections -fdata-sections"
	
clean:
	make clean  PREFIX=build_rv32