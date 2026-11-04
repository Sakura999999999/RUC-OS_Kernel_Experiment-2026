# MemoryStatus

* 添加一个内核模块，遍历page打印物理内存信息，指定进程后遍历并打印vma和页表信息。

## 操作指南

* 拷贝编译好的内核模块原目录到客户机中：

```bash
cp -r /tmp/share/practice_kern/MemoryStatus/ .
cd MemoryStatus
```

* 编译并运行target用户态程序（target pid会输出）：

```bash
make target && ./target &
```

* 指定pid后运行内核模块：

```bash
make load PID=<target pid>
```

## 实验要求

* 根据[export](../export.md)导出符号[__pte_offset_map](https://elixir.bootlin.com/linux/v6.6/source/mm/pgtable-generic.c#L280)。
* 根据[mem_stat.c](./mem_stat.c)中的TODO完善代码，并按照如上流程执行后可以得到：

```bash
user@kernel:/tmp/share/RUC-OS_Kernel_Experiment-2026/MemoryStatus$ make load PID=226
sudo insmod mem_stat.ko pid=226
[  104.183262] mem_stat: loading out-of-tree module taints kernel.
[  104.208453] [memory_status] ===== Page Frame Traversal =====
[  104.218399] [memory_status] ===== Page Type Summary =====
[  104.218612] [memory_status] total_pfn         = 786399
[  104.218727] [memory_status] valid_pfn         = 786399
[  104.218835] [memory_status] free_pages        = 737254
[  104.218948] [memory_status] anon_pages        = 2505
[  104.219166] [memory_status] file_pages        = 34097
[  104.219284] [memory_status] slab_pages        = 16470
[  104.219471] [memory_status] dirty_pages       = 2128
[  104.219600] [memory_status] writeback_pages   = 0
[  104.219711] [memory_status] lru_pages         = 19655
[  104.219821] [memory_status] PAGE_SIZE         = 4096 bytes
[  104.220076] [memory_status] ===== Target process: bash (pid=226) =====
[  104.220226] [memory_status] ===== Traverse VMA =====
[  104.220394] VMA: 0x4b9000 - 0x4d8000, flags=0x71, anon=0, file=bash
[  104.220536] VMA: 0x4d8000 - 0x596000, flags=0x75, anon=0, file=bash
[  104.220680] VMA: 0x596000 - 0x5f1000, flags=0x71, anon=0, file=bash
[  104.220804] VMA: 0x5f1000 - 0x5f3000, flags=0x100071, anon=0, file=bash
[  104.221013] VMA: 0x5f3000 - 0x5f8000, flags=0x100073, anon=0, file=bash
[  104.221169] VMA: 0x5f8000 - 0x601000, flags=0x100073, anon=1, file=(null)
[  104.221302] VMA: 0x1347000 - 0x138f000, flags=0x100073, anon=1, file=(null)
[  104.221541] VMA: 0xb7be0000 - 0xb7be2000, flags=0x71, anon=0, file=libnss_files-2.28.so
[  104.221754] VMA: 0xb7be2000 - 0xb7be9000, flags=0x75, anon=0, file=libnss_files-2.28.so
[  104.222087] VMA: 0xb7be9000 - 0xb7bec000, flags=0x71, anon=0, file=libnss_files-2.28.so
[  104.222257] VMA: 0xb7bec000 - 0xb7bed000, flags=0x70, anon=0, file=libnss_files-2.28.so
[  104.222576] VMA: 0xb7bed000 - 0xb7bee000, flags=0x100071, anon=0, file=libnss_files-2.28.so
[  104.222748] VMA: 0xb7bee000 - 0xb7bef000, flags=0x100073, anon=0, file=libnss_files-2.28.so
[  104.223167] VMA: 0xb7bef000 - 0xb7bf5000, flags=0x100073, anon=1, file=(null)
[  104.223319] VMA: 0xb7bfa000 - 0xb7c2c000, flags=0x71, anon=0, file=LC_CTYPE
[  104.223456] VMA: 0xb7c2c000 - 0xb7c2d000, flags=0x71, anon=0, file=LC_NUMERIC
[  104.223596] VMA: 0xb7c2d000 - 0xb7c2e000, flags=0x71, anon=0, file=LC_TIME
[  104.223734] VMA: 0xb7c2e000 - 0xb7da1000, flags=0x71, anon=0, file=LC_COLLATE
[  104.223882] VMA: 0xb7da1000 - 0xb7da2000, flags=0x71, anon=0, file=LC_MONETARY
[  104.224033] VMA: 0xb7da2000 - 0xb7da3000, flags=0x71, anon=0, file=SYS_LC_MESSAGES
[  104.224320] VMA: 0xb7da3000 - 0xb7daa000, flags=0xd1, anon=0, file=gconv-modules.cache
[  104.224497] VMA: 0xb7daa000 - 0xb7dac000, flags=0x100073, anon=1, file=(null)
[  104.224666] VMA: 0xb7dac000 - 0xb7dc5000, flags=0x71, anon=0, file=libc-2.28.so
[  104.224814] VMA: 0xb7dc5000 - 0xb7f13000, flags=0x75, anon=0, file=libc-2.28.so
[  104.224955] VMA: 0xb7f13000 - 0xb7f83000, flags=0x71, anon=0, file=libc-2.28.so
[  104.225100] VMA: 0xb7f83000 - 0xb7f84000, flags=0x70, anon=0, file=libc-2.28.so
[  104.225246] VMA: 0xb7f84000 - 0xb7f86000, flags=0x100071, anon=0, file=libc-2.28.so
[  104.225401] VMA: 0xb7f86000 - 0xb7f87000, flags=0x100073, anon=0, file=libc-2.28.so
[  104.225557] VMA: 0xb7f87000 - 0xb7f8a000, flags=0x100073, anon=1, file=(null)
[  104.225698] VMA: 0xb7f8a000 - 0xb7f8b000, flags=0x71, anon=0, file=libdl-2.28.so
[  104.226069] VMA: 0xb7f8b000 - 0xb7f8d000, flags=0x75, anon=0, file=libdl-2.28.so
[  104.226229] VMA: 0xb7f8d000 - 0xb7f8e000, flags=0x71, anon=0, file=libdl-2.28.so
[  104.226375] VMA: 0xb7f8e000 - 0xb7f8f000, flags=0x100071, anon=0, file=libdl-2.28.so
[  104.226528] VMA: 0xb7f8f000 - 0xb7f90000, flags=0x100073, anon=0, file=libdl-2.28.so
[  104.226712] VMA: 0xb7f90000 - 0xb7f97000, flags=0x71, anon=0, file=libtinfo.so.6.1
[  104.227126] VMA: 0xb7f97000 - 0xb7fa6000, flags=0x75, anon=0, file=libtinfo.so.6.1
[  104.227280] VMA: 0xb7fa6000 - 0xb7fb5000, flags=0x71, anon=0, file=libtinfo.so.6.1
[  104.227421] VMA: 0xb7fb5000 - 0xb7fb6000, flags=0x70, anon=0, file=libtinfo.so.6.1
[  104.227562] VMA: 0xb7fb6000 - 0xb7fb8000, flags=0x100071, anon=0, file=libtinfo.so.6.1
[  104.227710] VMA: 0xb7fb8000 - 0xb7fb9000, flags=0x100073, anon=0, file=libtinfo.so.6.1
[  104.227863] VMA: 0xb7fb9000 - 0xb7fba000, flags=0x71, anon=0, file=LC_PAPER
[  104.228125] VMA: 0xb7fba000 - 0xb7fbb000, flags=0x71, anon=0, file=LC_NAME
[  104.228299] VMA: 0xb7fbb000 - 0xb7fbc000, flags=0x71, anon=0, file=LC_ADDRESS
[  104.228448] VMA: 0xb7fbc000 - 0xb7fbd000, flags=0x71, anon=0, file=LC_TELEPHONE
[  104.228592] VMA: 0xb7fbd000 - 0xb7fbe000, flags=0x71, anon=0, file=LC_MEASUREMENT
[  104.228754] VMA: 0xb7fbe000 - 0xb7fc0000, flags=0x100073, anon=1, file=(null)
[  104.228894] VMA: 0xb7fc0000 - 0xb7fc4000, flags=0x4044411, anon=0, file=(null)
[  104.229295] VMA: 0xb7fc4000 - 0xb7fc6000, flags=0x40075, anon=0, file=(null)
[  104.229444] VMA: 0xb7fc6000 - 0xb7fc7000, flags=0x71, anon=0, file=ld-2.28.so
[  104.229580] VMA: 0xb7fc7000 - 0xb7fe3000, flags=0x75, anon=0, file=ld-2.28.so
[  104.229712] VMA: 0xb7fe3000 - 0xb7fed000, flags=0x71, anon=0, file=ld-2.28.so
[  104.229845] VMA: 0xb7fed000 - 0xb7fee000, flags=0x71, anon=0, file=LC_IDENTIFICATION
[  104.229988] VMA: 0xb7fee000 - 0xb7fef000, flags=0x100071, anon=0, file=ld-2.28.so
[  104.230127] VMA: 0xb7fef000 - 0xb7ff0000, flags=0x100073, anon=0, file=ld-2.28.so
[  104.230263] VMA: 0xbfdac000 - 0xbfdcd000, flags=0x100173, anon=1, file=(null)
[  104.230444] [memory_status] ===== Page Table Walk (partial) =====
[  104.230646] VA 0x4d8000 -> PFN 0xbe934 (PA 0xbe934000)
[  104.230759] VA 0x4d9000 -> PFN 0xbc84b (PA 0xbc84b000)
[  104.230887] VA 0x4da000 -> PFN 0xbc84c (PA 0xbc84c000)
...
[  104.601506] VA 0xbfdca000 -> PFN 0xbd853 (PA 0xbd853000)
[  104.602852] VA 0xbfdcb000 -> PFN 0xbd118 (PA 0xbd118000)
[  104.605752] VA 0xbfdcc000 -> PFN 0xbb40b (PA 0xbb40b000)
[  104.615217] [memory_status] Mapped pages: 399
```

## 参考材料

https://tldp.org/LDP/tlk/mm/memory.html
