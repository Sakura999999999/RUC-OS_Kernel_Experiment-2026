# 环境搭建

## VMware

* [vmware云盘链接](https://pan.ruc.edu.cn/link/AAC2DAE7A9334149F9913389186D7694B1)
    * LinuxKernel.zip：图形化界面，开销高、操作方便；
    * LinuxKernel-server：非图形化界面，占用空间少、需要远程链接（推荐用VSCode Remote-SSH）。

请下载链接中的任一VMware虚拟机（推荐使用server版），解压后找到ovf文件，参考[VMware导入ova/ovf虚拟机文件](https://blog.csdn.net/Highlight_Jin/article/details/138542710)。

## 远程链接

导入ovf后打开虚拟机，默认用户为user，密码为abcd1234。登录后查看虚拟机IP地址：

``` bash
user@os-kern-exp:~/Docker$ ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host
       valid_lft forever preferred_lft forever
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP group default qlen 1000
    link/ether 00:0c:29:2d:14:4e brd ff:ff:ff:ff:ff:ff
    altname enp2s1
    inet 192.168.20.129/24 metric 100 brd 192.168.20.255 scope global dynamic ens33
       valid_lft 1029sec preferred_lft 1029sec
    inet6 fe80::20c:29ff:fe2d:144e/64 scope link
       valid_lft forever preferred_lft forever
```

> 如果下载的是图形化版本，请打开终端执行上述命令。

这里显示虚拟机的IP为192.168.20.129，然后按照[官方教程](https://code.visualstudio.com/docs/remote/ssh)在VSCode中安装插件并配置虚拟机IP：

``` conf
Host OS-Kernel-Experiment
    HostName 192.168.20.129
    User user
```

这样以来我们就可以开启虚拟机后，通过VSCode远控了。

## Ubuntu宿主机

> 上述提到的虚拟机就是Ubuntu宿主机。

目录结构（Host）
* ${HOME}/Kernel：内核
    * compile：内核编译脚本
    * git：内核源代码仓库
    * image：硬盘镜像（区分i386和x86_64，支持多个Ubuntu版本）
    * share：Host与Guest的共享文件夹（Host端）
    * v5.x：Linux内核v5.x源代码和可执行程序（区分i386和x86_64）
* ${HOME}/Workspace：模拟器
    * run、debug、script：运行和调试脚本
    * scp、ssh：远程连接和远程文件传输脚本（Host与Guest互连、互传文件）
    * compile、src、build、exe：QEMU编译脚本、源代码、中间文件和可执行文件

目录结构（Guest）
* /tmp/linux：内核源代码（从Host端映射到Guest端）
* /tmp/share：Host与Guest的共享文件夹（Guest端）

# 环境运行

由于本学期实验使用的都是i386架构，故需要更新WorkSpace中的run.sh中的qemu启动命令。具体命令见scripts/run.sh。

* 编译内核（进入${HOME}/Kernel目录）

``` bash
./compile <kernel-tag> <arch>

# 实例
./compile v6.0 i386
```

![setup_compile](./images/setup_compile.png)

* 运行内核（进入${HOME}/WorkSpace目录）

``` bash
./run <kernel-tag> <arch> <image>

# 实例
./run v6.0 i386 buster
```

![setup_run](./images/setup_run.png)