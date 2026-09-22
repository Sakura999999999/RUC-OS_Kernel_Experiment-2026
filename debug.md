# 内核调试

成功编译运行内核（见[setup](./setup.md)）之后，接下来我们使用gdb来调试内核。

## QEMU参数设置

查看scripts/debug.sh，可以看到运行QEMU的命令：

``` bash
qemu-system-i386 \
    -snapshot \
    -s -S \
    -m 4G \
    -smp 2 \
    -kernel ${KERNEL} \
    -append "nokaslr console=ttyS0 root=/dev/sda earlyprintk=serial net.ifnames=0" \
    -drive file=${HDA},format=raw \
    -nographic \
    -net user,host=10.0.2.10,hostfwd=tcp:127.0.0.1:10021-:22 \
    -net nic,model=e1000 \
    -fsdev local,security_model=passthrough,id=fsdev0,path=${LINUX} \
    -device virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostlinux \
    -fsdev local,security_model=passthrough,id=fsdev1,path=${SHARE} \
    -device virtio-9p-pci,id=fs1,fsdev=fsdev1,mount_tag=hostshare \
    -pidfile vm.pid \
    -cpu qemu32 \
    2>&1 | tee vm.log
```

* 其中`-s`等价于 -gdb tcp::1234，即在默认的 TCP 端口 1234 上启动一个 gdb 服务器。
这允许用户通过 gdb 连接到 QEMU 实例进行调试。
* `-S`表示在启动时暂停虚拟机的 CPU。
这通常与 -s 一起使用，方便在虚拟机启动前通过 gdb 连接并设置断点。

当我们添加`-s`参数时，QEMU运行内核后就可以通过gdb远程连接了。

## 运行演示

启用`-s -S`后运行run.sh，可以看到QEMU在等待gdb连接：

![images/debug_kernel.png](./images/debug_kernel.png)

运行脚本debug.sh（替换{target_function}为你想断点停下的内核函数）：

``` bash
gdb vmlinux \
    -ex "target remote:1234" \
    -ex "b {target_function}" \
    -ex "c"
```

把{target_function}设置为ksys_read之后运行内核：

![images/gdb_qemu.png](./images/gdb_qemu.png)

在左下角我们可以看到，内核在Breakpoint 1，也就是ksys_read的断点处停下了。这是因为运行的内核时刻有进程在调用该函数，触发了断点。

但是当前内核没有调试信息，导致我们在断点停下后无法看到对应的源码信息。这时候我们需要为内核添加调试信息，即给内核添加CONFIG_DEBUG_INFO编译选项。

> 由于此选项默认打开，故下面的配置可跳过。这里演示的是未打开此选项的操作流程。

在宿主机中的源码目录下，执行make menuconfig打开图形化配置内核编译选项：

![images/menuconfig.png](./images/menuconfig.png)

进入后输入`/`开启搜索模式，然后输入DEBUG_INFO后回车：

![images/menuconfig_debug_info.png](./images/menuconfig_debug_info.png)

![images/menuconfig_debug_info_res.png](./images/menuconfig_debug_info_res.png)

按(1)进入后按空格打开选项：

![images/menuconfig_debug_info_res_blank.png](./images/menuconfig_debug_info_res_blank.png)

回车进入DWARF版本配置项后，选择`Generate DWARF Version 5 debuginfo`，空格启用：

![images/menuconfig_debug_dwarf5.png](./images/menuconfig_debug_dwarf5.png)

最后我们连按Esc退出并保存即可。

之后我们重新编译内核，此时内核就有调试信息了。

## 实验：观察指定程序退出时的退出码/pid

在宿主机的一个终端中启动带有 `-s -S` 参数的 QEMU（scripts/debug.sh）：

```bash
cd ~/WorkSpace
./debug.sh v6.0 i386 buster
```

并在另一个终端中连接 GDB：

```bash
gdb /home/user/Kernel/v6.0/i386/vmlinux
```

先在 GDB 中执行：

```gdb
target remote:1234
c
```

QEMU 启动完成后，在 GDB 中按 `Ctrl-C`，为 `do_exit()` 函数设置断点。

```gdb
b do_exit
c
```

之后在 QEMU 中运行如下目标进程，并记录它的 PID：

```bash
sleep 10 & # 后台运行一个进程
echo $!
```

当进程结束时，内核运行至断点函数 `do_exit()` 停下了，此时可用 GDB 进行调试。

Task 1：打印 do_exit 函数的退出码。

（选做）Task 2：打印该进程的 pid。
