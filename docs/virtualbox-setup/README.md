# How to setup VirtualBox on Windows

为了保证统一的编程环境，课程为同学们准备了虚拟机镜像。虚拟机是一种硬件虚拟化技术。它允许用户将一台计算机虚拟为多台逻辑计算机。每个逻辑计算机可运行不同的操作系统，并且应用程序都可以在相互独立的空间内运行而互不影响，从而显著提高计算机的工作效率。


## 准备虚拟机管理程序

虚拟机管理程序（Hypervisor）一种运行在基础物理服务器和操作系统之间的中间软件层，可允许多个操作系统和应用共享硬件。也可叫做VMM(Virtual Machine Monitor )，即虚拟机监视器。
 
课程推荐同学们使用免费开源的VirtualBox作为Hypervisor。可以从[VirutalBox官网](https://www.virtualbox.org/)下载VirtualBox软件

![](img/3657f575-4a01-48a3-8ce4-bb25cd67a665.png)

选择Windows hosts

![](img/0bcf163a-0582-4d36-80c0-c50cdbe9dafc.png)

[JBOX备用链接](https://jbox.sjtu.edu.cn/l/t19GAn)

下载后，根据软件的提示完成安装

![](img/64933f25-c1c6-49be-81a7-5b946ce9b22d.png)

双击

![](img/056b4397-9241-4e92-8ac5-a2a63a9d8305.png)

下一步

![](img/d3eb66b9-a4d3-4da1-8012-475d6e395185.png)

下一步

![](img/18f21888-79b9-4a8e-b228-ed61ba7e9fca.png)

下一步

![](img/43c8a8fb-6041-4a0d-935c-b0a9c9393812.png)

是

![](img/cfc407d5-c01c-44e1-a105-0e8d33589b9a.png)

安装


> 另外，市场上还有很多其他的虚拟机管理程序，如Hyper-V（Windows）、VMware Workstation（Windows & Linux）、VMware Fusion（MacOS）、Parallel Desktop（MacOS）、QEMU（ALL）

## 下载虚拟机镜像

从JCloud下载所需的虚拟机镜像。[下载链接](https://jbox.sjtu.edu.cn/l/91CPDj)

![](img/1f409b8f-55fd-41f1-8fff-0344f74a45f6.png)

![](img/4756a4ea-0f47-4e7a-9374-954d078c8445.png)



## 从镜像新建虚拟机并完成配置

从开始菜单或者桌面快捷方式启动VirtualBox，选择导入虚拟电脑
![](img/6187358e-71a8-4d4b-bdd3-1c94e276592a.png)

选择需要导入的虚拟机，这里选择上一步下载的`ice3302p.ova`，然后点击下一步

![](img/6a5a524e-c131-4732-a4d8-745dde18f02f.png)


这里可以修改导入虚拟机的各项设置

![](img/d642bb68-99de-4694-97e5-a009294cb840.png)

参考图例修改配置后导入虚拟机，虚拟机导入需要一定的时间

## 登陆虚拟机

虚拟机导入后，可以点击启动按钮启动虚拟机。虚拟机将自动捕获鼠标键盘输入，按下Right Ctrl释放，从而在宿主系统（Windows）中使用鼠标

![](img/7568cfa3-f106-4448-bcfb-f697a29deb32.png)

一般来说，虚拟机是无法启动的（网络错误）

![](img/ce399826-c1d7-4a39-a1dd-9db32308605a.png)

这里选择更改网络设置，并更改网络设置为网络地址转换，点击OK保存。虚拟机应该能够正常启动

![](img/57aa37af-9543-450c-8de6-8d83e82fb836.png)

虚拟机中的账户名称为`ice3302p`，密码为`ice3302p`。如下图所示，输入密码后，就可以登陆到Ubuntu系统中

![](img/5da5ef84-376d-4729-abf5-3479fd914d7d.png)

### 测试

新建一个helloworld目录

![](img/611f8f17-903e-4acb-9eec-0fb8d03a89c3.png)

在终端中打开该目录

![](img/07d9f13d-45c9-44be-9465-3bb79475c9b1.png)

输入`code .`并回车，这将会启动VSCode并定位到该目录，选择`Yes, I trust the authors`

![](img/7d8e00f9-8a8d-4aa0-a2c4-d63a210ddb14.png)

![](img/861857b2-1392-48e6-8f27-df3accc8e75e.png)


新建文件`main.c`，随便输入一段代码

![](img/daca3bd6-941f-4e0a-a0b6-0885c848fa6b.png)

![](img/7f019c2f-9882-4180-9869-34103b881f01.png)

打开终端面板，输入`gcc main.c -o main`，回车执行，如果什么都没有提示就说明万事大吉

![](img/e2e24d4a-947d-4af8-a0f6-540b0fb574fb.png)

![](img/697b9be6-d941-4509-a279-e998904cbcf5.png)

我们刚才执行的命令在当前目录下生成了`main`可执行文件，输入`./main`来执行它

![](img/ac65af68-be6c-48c4-a40b-9dd42dae0b59.png)

如果我们输入的命令在运行中产生了错误，该行命令前的提示符会变成红色

![](img/feb35a1c-4e9a-4cdb-a76c-1cba4657c92c.png)
