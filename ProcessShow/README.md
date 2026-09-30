# ProcessShow

* 添加一个内核模块，加载模块时打印内核中所有进程的状态。

## 环境准备

* （可选）编译指定版本内核，实验中采用v6.0。

```bash
cd ~/Kernel
./compile v6.0 i386
```

* 拷贝仓库源码到宿主机的共享文件夹。

```bash
cd ~/Workdir/share
git clone https://github.com/Sakura999999999/RUC-OS_Kernel_Experiment-2026.git
mv RUC-OS_Kernel_Experiment-2026 practice_kern
```

* 进入项目目录。

```bash
cd practice_kern/ProcessShow
```

* 确认[Makefile](Makefile)中路径是否正确。

```Makefile
# 目标内核的根目录（确认是否存在对应目录）
LINUX_KERNEL_PATH := /home/user/Kernel/v6.0/i386/
```

* 编译内核模块。

```bash
make
```

生成 `process_show.ko` 文件。

## 实验运行

* 启动qemu运行编译好的内核。

```bash
./run v6.0 i386 buster
```

* 用户为user，无密码。

```bash
kernel login: user
```

> 接下来的操作都在客户机中。

* 拷贝实验目录到客户机本地。

```bash
cp -r /tmp/share/practice_kern/ProcessShow .
cd ProcessShow
```

* 加载内核模块process_show。

```bash
make load
```

* 输出结果如下：

```plain
user@kernel:/tmp/share/practice_kern/ProcessShow$ make load
sudo insmod process_show.ko
[  342.506956][ T7897] process_show: loading out-of-tree module taints kernel.
[  342.507358][ T7897] process_show: module verification failed: signature and/or required key missing l
[  342.508138][ T7897] === Start showing process list ===
[  342.508424][ T7897] PID: 1      | State: INTERRUPTIBLE    | Command: systemd
[  342.508804][ T7897] PID: 2      | State: INTERRUPTIBLE    | Command: kthreadd
[  342.509198][ T7897] PID: 3      | State: INTERRUPTIBLE    | Command: pool_workqueue_
[  342.509615][ T7897] PID: 4      | State: UNKNOWN          | Command: kworker/R-rcu_g
[  342.510029][ T7897] PID: 5      | State: UNKNOWN          | Command: kworker/R-rcu_p
[  342.510446][ T7897] PID: 6      | State: UNKNOWN          | Command: kworker/R-slub_
[  342.510858][ T7897] PID: 7      | State: UNKNOWN          | Command: kworker/R-netns
[  342.511278][ T7897] PID: 8      | State: UNKNOWN          | Command: kworker/0:0
[  342.511673][ T7897] PID: 9      | State: UNKNOWN          | Command: kworker/0:1
[  342.512067][ T7897] PID: 13     | State: UNKNOWN          | Command: kworker/R-mm_pe
[  342.512489][ T7897] PID: 14     | State: UNKNOWN          | Command: rcu_tasks_kthre
[  342.512907][ T7897] PID: 15     | State: UNKNOWN          | Command: rcu_tasks_trace
...
```

* （可选）卸载内核模块process_show。

```bash
make unload
```

* （可选）使用`CTRL+A+X`退出内核运行。

## 实验要求

1. 打印进程的执行权限值（euid、egid）。

```c
struct cred {
    ...
    kuid_t		euid;		/* effective UID of the task */
    kgid_t		egid;		/* effective GID of the task */
    ...
}
```

2. 打印进程的父进程pid。
3. 解析并打印进程对应的thread_info。