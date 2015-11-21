all: simdisk

simdisk: simulator_disk.c
	gcc -o simdisk simulator_disk.c

clean: rm simdisk
