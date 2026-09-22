obj-m += student_list.o
CURRENT_PATH := $(shell pwd)
VERSION := v6.0
ARCH := i386
LINUX_KERNEL_PATH := /home/user/Kernel/$(VERSION)/$(ARCH)/

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

load:
	sudo insmod student_list.ko

unload:
	sudo rmmod student_list

user:
	gcc student_ioctl.c -o student_ioctl

run:
	sudo ./student_ioctl