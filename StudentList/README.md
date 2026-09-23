# StudentList

* 实现一个内核模块，管理学生链表，并支持用户进程增删查。

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

### 实验场景与功能

本实验实现一个简单的学生信息与考试成绩管理模块。用户态程序通过 `ioctl` 与内核模块交互，内核模块负责保存学生信息、接收成绩事件并维护成绩排名。

实验流程如下：

1. 用户态程序向内核添加多名学生，记录学生的学号和姓名。
2. 内核使用 `list` 保存全部学生记录，使用 `hlist` 建立按年级和学院查询的索引。
3. 用户态程序可以根据年级或学院查询学生，查询结果通过内核日志输出。
4. 用户态程序提交学生成绩。提交的数据包含原始学号和成绩，内核根据学号找到对应学生，并获取该学生的 IDR 内部编号。
5. 内核将“IDR 编号和成绩”组成成绩记录，按提交顺序放入 `kfifo`。
6. 查询最高分时，内核按照先进先出的顺序处理成绩记录，并更新学生成绩。
7. 已录入成绩的学生通过 `rbtree` 按成绩维护排名，成绩相同时按 IDR 编号排序。
8. 用户态程序可以查询当前最高分学生，也可以重新提交成绩，内核会更新红黑树中的排名。

本实验使用的主要内核数据结构包括：

- `list`：保存全部学生记录；
- `hlist`：按年级和学院建立查询索引；
- `IDR`：为每个学生分配内核内部编号；
- `kfifo`：缓存待处理的成绩事件；
- `rbtree`：维护学生成绩排名。

主要 `ioctl` 操作包括：

- `STUDENT_ADD`：添加学生；
- `STUDENT_DEL`：按学号删除学生；
- `STUDENT_QUERY_GRADE`：按年级查询学生；
- `STUDENT_QUERY_COLLEGE`：按学院查询学生；
- `STUDENT_SUBMIT_SCORE`：提交学生成绩；
- `STUDENT_QUERY_TOP`：查询当前最高分学生。

### 实验输出

* 请实现内核模块的TODO，使得进入客户机后编译运行（make user && make run）用户态程序，能够得到正确输出。

``` bash
user@kernel:/tmp/share/RUC-OS_Kernel_Experiment-2026/StudentList$ make run
sudo ./student_ioctl
[  984.053798] Added student 2023103111 Alice
[  984.061966] Added student 2022201456 Bob
[  984.065771] Added student 2023103122 Carol
[  984.071621] Added student 2022202457 David
[  984.072775] Added student 2024103113 Eve
[  984.073020] Added student 2023201789 Frank
[  984.073869] Added student 2023103555 Grace
[  984.074323] Added student 2023201333 Heidi
[  984.074673] Added student 2022201999 Ivan
[  984.074951] Added student 2024103666 Judy
[  984.075466] Query grade 2023 (see kernel log for results)
[  984.075985] Grade 2023: 2023201333 Heidi
[  984.076374] Grade 2023: 2023103555 Grace
[  984.076915] Grade 2023: 2023201789 Frank
[  984.077074] Grade 2023: 2023103122 Carol
[  984.077190] Grade 2023: 2023103111 Alice
[  984.077694] Query grade 2022 (see kernel log for results)
[  984.078165] Grade 2022: 2022201999 Ivan
[  984.078424] Grade 2022: 2022202457 David
[  984.078597] Grade 2022: 2022201456 Bob
[  984.078804] Query college 103 (see kernel log for results)
[  984.079127] College 103: 2024103666 Judy
[  984.079391] College 103: 2023103555 Grace
[  984.080341] College 103: 2024103113 Eve
[  984.081443] College 103: 2023103122 Carol
[  984.082984] College 103: 2023103111 Alice
[  984.083276] Query college 201 (see kernel log for results)
[  984.083524] College 201: 2022201999 Ivan
[  984.083922] College 201: 2023201333 Heidi
[  984.084119] College 201: 2023201789 Frank
[  984.084529] College 201: 2022201456 Bob
[  984.084895] Submitted score: 2023103111 88
[  984.085114] Submitted score: 2022201456 95
[  984.085499] Submitted score: 2023103122 91
[  984.085727] Submitted score: 2022202457 76
[  984.086028] Submitted score: 2024103113 84
[  984.086467] Submitted score: 2023201789 90
[  984.086730] Submitted score: 2023103555 87
[  984.086941] Submitted score: 2023201333 93
[  984.087206] Submitted score: 2022201999 79
[  984.087934] Submitted score: 2024103666 89
[  984.088180] Query top student (see kernel log for results)
[  984.089419] Top student: 2022201456, score=95
[  984.089871] Submitted score: 2023103111 99
[  984.090192] Query top student (see kernel log for results)
[  984.090556] Top student: 2023103111, score=99
```
