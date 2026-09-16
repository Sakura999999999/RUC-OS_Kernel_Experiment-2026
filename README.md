# 操作系统内核分析及安全实验

## 环境

* [录屏下载链接](https://pan.ruc.edu.cn/link/AA4B18EAA538F94CD9AAC8D1A435B6D1AB)
* [环境下载链接](https://pan.ruc.edu.cn/link/AA3FBA9D90E0CF44E0B7E0D12EF02DC782)
  * VMWare虚拟机的两个虚拟化选项不是必选。
  * 宿主机用户user，密码abcd1234。
* [环境搭建文档](./setup.md)
* [内核调试文档](./debug.md)
* [gdb操作文档](https://sourceware.org/gdb/current/onlinedocs/gdb#Commands)

### 环境说明

可以简要概括为宿主机（host）中编译内核，客户机（guest）运行内核并加载内核模块等。

## 章节实验

| 章节             | 实验                          | 大作业       |
| ---------------- | ----------------------------- | ------------ |
| 一、Linux 内核概述 | [DebugKernel](./debug.md)         | -            |
| 二、进程管理与调度 | [ProcessShow](./ProcessShow) / [ScheduleObserver](./ScheduleObserver/)| [HideProcess](./RootKit/HideProcess) |
| 三、系统调用       | [SyscallShow](./SyscallShow) / [AddSyscall](./AddSyscall/)| [HookSyscall](./RootKit/HookSyscall/) |
| 四、存储管理       | [MemoryStatus](./MemoryStatus/) / [TraverseVMA](./TraverseVMA)   | [HideVMA](./RootKit/HideVMA/)     |
| 五、文件系统       | [StatPlus](./StatPlus/) / [ProcMirror](./ProcMirror/) | [RedirectFile](./RootKit/RedirectFile/) |
| 六、进程间通信     | [MutiIPC](./MutiIPC/) / [CheatIPC](./CheatIPC/)   | [SignalBlocker](./RootKit/SignalBlocker/) |
| 七、内核同步       | [RaceCondition](./RaceCondition/) / [VisitShared](./VisitShared/) | - |
| 八、中断机制       | - / -     | [IDTHook](./RootKit/IDTHook/) |
|安全|[codeql](./Security/codeql/) / [syzkaller](./Security/syzkaller/)| - |

### ProcessShow

* 添加一个内核模块，加载模块时打印内核中所有进程的状态。

* [step-by-step](ProcessShow/README.md)

### ShowVruntime

* 展示10s指定进程的vruntime。

### ScheduleObserver

* 添加一个内核模块，加载模块时创建多个线程，线程中会让出CPU并记录被调用的次数，卸载模块时会打印每个线程被执行的次数。

* [step-by-step](ScheduleObserver/README.md)

### SyscallShow

* 添加一个内核模块，加载模块时打印内核中所有系统调用。

* [step-by-step](./SyscallShow//README.md)

### MemoryStatus

* 添加一个内核模块，加载模块时打印内核的物理内存状态。

* [step-by-step](MemoryStatus/README.md)

### TraverseVMA

* 添加一个内核模块，翻转指定进程VMA的写位。

* [step-by-step](./TraverseVMA//README.md)


### AddSyscall

* 添加一个内核模块，加载模块时添加一个系统调用。

* [step-by-step](./AddSyscall/README.md)

### AddMyEXT4

* 应用补丁，添加一个myext4文件系统。

* [step-by-step](./AddMyEXT4/README.md)

### CreateProc

* 添加一个内核模块，加载模块时在proc文件系统中添加一个目录和文件。

* [step-by-step](./CreateProc/README.md)

### StatPlus

* 添加一个内核模块，打印指定进程的 fd（默认 3）对应文件的详细信息（路径、类型、权限、owner、size、inode、时间戳等）。

* [step-by-step](./StatPlus/README.md)

### ProcMirror

* 添加一个内核模块，在 `/proc` 下创建 `proc_mirror` 目录，用符号链接映射目标进程已打开的文件（`fd-<N>` -> 文件路径）。

* [step-by-step](./ProcMirror/README.md)

### IPCtest

* 课堂演示：测试所有进程间通信方式的性能。

* [step-by-step](./IPCtest/README.md)

### BinderIPC

* 两个用户态程序（客户端和服务端），通过binder进行IPC。

* [step-by-step](./BinderIPC/README.md)

### MutiIPC

* 一个最小化 Fuzz 练习框架，演示并练习多种 IPC 的协作。

* [step-by-step](./MutiIPC/README.md)

### CheatIPC

* 添加一个内核模块，篡改消息队列中的消息内容使得程序行为改变。

* [step-by-step](./CheatIPC/README.md)

### RaceCondition

* 添加两个系统调用，使得在不实施内核同步控制的情况下，用户调用系统调用，会经过不同的内核路径，从而触发共享变量的不一致。

* [step-by-step](./RaceCondition/README.md)

### VisitShared

* 添加一个内核模块，加载模块时通过中断处理函数、异常处理函数、可延迟函数访问一个自建的共享变量。

* [step-by-step](./VisitShared/README.md)

## RootKit

### HideProcess

* 添加一个内核模块，将指定进程从链表中摘除，使得ProcessShow无法检测到该进程。

* [step-by-step](RootKit/HideProcess/README.md)

### HookSyscall

* 添加一个内核模块，hook系统调用setuid，使得恶意进程通过该系统调用提权。

* [step-by-step](./RootKit/HookSyscall/README.md)

### HideVMA

* 添加一个内核模块，将指定进程的VMA隐藏。

* [step-by-step](./RootKit/HideVMA/README.md)

### IDTHook

* 添加一个内核模块，注册一个键盘监控，打印每个键盘按键。

* [step-by-step](./RootKit/IDTHook/README.md)

### RedirectFile

* 添加一个内核模块，将指定进程打开的文件重定向到另一个文件（如`/etc/passwd`）。

* [step-by-step](./RootKit/RedirectFile/README.md)

### SignalBlocker

* 添加一个内核模块，在内核中捕获发给malware的信号并记录。

* [step-by-step](./RootKit/SignalBlocker/README.md)

## Security

### codeql

* 使用CodeQL检测在内核中预埋的漏洞。

* [step-by-step](./Security/codeql/README.md)

### syzkaller

* 使用Syzkaller模糊测试在内核中预埋的漏洞。

* [step-by-step](./Security/syzkaller/README.md)

## 前置知识

### Linux 内核

![alt text](images/kernel_arch.png)

![alt text](images/kernel_code_arch.png)

### 内核模块

内核模块是一种可以动态加载到Linux内核中的代码，允许在不重新编译或重启内核的情况下扩展内核功能。这种机制为Linux提供了极大的灵活性，使用户可以根据需要添加或删除功能，而不必重新编译整个内核。

但内核模块也存在其缺陷，比如如果内核模块中有 bug 会导致整个系统崩溃，不同内核模块通常依赖于特定的版本等。

### QEMU

QEMU 的原理及使用可参考 https://wokron.github.io/posts/qemu-introduction/ 。
