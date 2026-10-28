obj-m += traverse_vma.o

# 当前模块的路径
CURRENT_PATH := $(shell pwd)

# 目标内核的根目录（确认是否存在对应目录）
LINUX_KERNEL_PATH := /home/user/Kernel/v6.0/i386/

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

load:
	sudo insmod traverse_vma.ko pid=$(PID)

unload:
	sudo rmmod traverse_vma

target:
	gcc target.c -o target