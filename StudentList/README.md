# StudentList

* 实现一个内核模块，管理学生链表，并支持用户进程增删查。

## 环境准备

* 编译指定版本内核，实验中采用v6.0。因为需要编译内核模块，所以要将 compile 脚本的最后改为 ``make -j`nproc` ``，不仅指定编译产物为 bzImage。随后运行 compile 脚本。

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
cd practice_kern/StudentList
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

生成 `student_list.ko` 文件。

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
cp -r /tmp/share/practice_kern/StudentList .
cd StudentList
```

* 加载内核模块student_list。

```bash
make load
```

* 编译运行（make user && make run）用户态程序，该程序会通过ioctl操作内核中的用户链表，具体测试样例见student_ioctl.c。

* （可选）卸载内核模块student_list。

```bash
make unload
```

* （可选）使用`CTRL+A+X`退出内核运行。

## 实验要求

* 请实现内核模块的TODO，使得进入客户机后编译运行（make user && make run）用户态程序，能够得到正确输出。

``` bash
user@kernel:/tmp/share/RUC-OS_Kernel_Experiment-2026/StudentList$ make run
sudo ./student_ioctl
[ 1004.580009] Added student 2023103111 Alice
Added: 2023103111 Alice
[ 1004.585396] Added student 2022201456 Bob
Added: 2022201456 Bob
[ 1004.586959] Added student 2023103122 Carol
Added: 2023103122 Carol
[ 1004.587698] Added student 2022202457 David
Added: 2022202457 David
[ 1004.588251] Added student 2024103113 Eve
Added: 2024103113 Eve
[ 1004.589096] Added student 2023201789 Frank
Added: 2023201789 Frank
[ 1004.589909] Added student 2023103555 Grace
Added: 2023103555 Grace
[ 1004.590860] Added student 2023201333 Heidi
Added: 2023201333 Heidi
[ 1004.591626] Added student 2022201999 Ivan
Added: 2022201999 Ivan
[ 1004.592155] Added student 2024103666 Judy
Added: 2024103666 Judy

Query grade 2023 (see kernel log for results)
[ 1004.593547] Grade 2023: 2023201333 Heidi
[ 1004.593809] Grade 2023: 2023103555 Grace
[ 1004.594012] Grade 2023: 2023201789 Frank
[ 1004.594213] Grade 2023: 2023103122 Carol
[ 1004.594536] Grade 2023: 2023103111 Alice

Query grade 2022 (see kernel log for results)
[ 1004.595691] Grade 2022: 2022201999 Ivan
[ 1004.595949] Grade 2022: 2022202457 David
[ 1004.596118] Grade 2022: 2022201456 Bob

Query college 103 (see kernel log for results)
[ 1004.597221] College 103: 2024103666 Judy
[ 1004.597659] College 103: 2023103555 Grace
[ 1004.597833] College 103: 2024103113 Eve
[ 1004.598093] College 103: 2023103122 Carol
[ 1004.598309] College 103: 2023103111 Alice

Query college 201 (see kernel log for results)
[ 1004.599487] College 201: 2022201999 Ivan
[ 1004.599658] College 201: 2023201333 Heidi
[ 1004.599906] College 201: 2023201789 Frank
[ 1004.600066] College 201: 2022201456 Bob

Submit student scores (see kernel log for results)
[ 1004.601189] Submitted score: 2023103111 88
[ 1004.601454] Submitted score: 2022201456 95
[ 1004.601824] Submitted score: 2023103122 91
[ 1004.602050] Submitted score: 2022202457 76
[ 1004.602225] Submitted score: 2024103113 84
[ 1004.602798] Submitted score: 2023201789 90
[ 1004.603001] Submitted score: 2023103555 87
[ 1004.603282] Submitted score: 2023201333 93
[ 1004.603713] Submitted score: 2022201999 79
[ 1004.603909] Submitted score: 2024103666 89

Query top student (see kernel log for results)
[ 1004.605079] Top student: 2022201456, score=95

Update Alice score and query top student (see kernel log for results)
[ 1004.606236] Submitted score: 2023103111 99
[ 1004.606872] Top student: 2023103111, score=99
```
