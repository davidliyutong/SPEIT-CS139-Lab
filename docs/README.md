# How to start writting in C

## 编程语言（Programming Language）是什么

在日常生活中，人们为了教他人做事，会使用自然语言（Natural Language）“控制”他人。自然语言往往有特定的格式（语法）、关键词，例如：

```text
下班顺路买一斤包子带回来，如果看到卖西瓜的，买一个。
```

其中**买**、**如果**、**看到**等词语具有特定的含义。通过这样一句话，人们就可以让同伴为他们购物

可以看到，示例的自然语言并没有严格遵守语法规定。它并没有指定看到卖西瓜的之后应该额外购买一个包子、退而只买一个包子还是额外购买一个西瓜。人类可以通过尝试来判断（比如晚饭不能只吃一个包子），而计算机只能执行明确的指令。

这些指令在如今的计算机系统中普遍以二进制的命令存在。当计算机的控制器收到电信号构成的指令后，它会分析并执行这些指令。

这就是最原始的编程方式。然而二进制构成的指令并不容易被人理解，也不利于写出正常人能看懂的程序。于是在计算机发展的早期阶段，普通人并不能参与到计算机软件的编写中。

为了提高计算机软件的生产力，编程语言（Programming Language）被发明出来。它们建立了**抽象的、人类可以理解的编程语句**与**具体的二进制代码**间的关系，使得人类编程人员可以通过自己熟悉的符号编写复杂的计算机指令。并使用编译器（Compiler）等自动化的程序将其生成，从而大幅度地减轻了软件开发的难度。

简单来讲是这样一种流程：

人们比较容易看懂的指令（代码） --> 编程语言的工具（编译器？）--> 计算机容易看懂的指令（二进制文件）

具体来说，所谓**编程语言的工具**五花八门，多种多样。编译型通过编译器生成二进制文件，可以直接在目标计算机上执行。解释型语言可以利用**解释器**实时**解释**代码。Java 等语言属于半编译半解释语言，可以生成字节码，在对应的虚拟机上执行。

## 开始入门 C

回顾一下这个流程

> 人们比较容易看懂的指令（代码） --> 编程语言的工具（编译器？）--> 计算机容易看懂的指令（二进制文件）

有 C 语言的对应版本

> C 代码 --> C 编译器 --> 二进制文件

每一个步骤都需要对应的工具进行完成。

### 编辑器

为了编写 C 代码，首先需要一个文本编辑器。该编辑器可以是几乎任何东西（只要能够编辑文字）在此列举一些：
|平台|实例（星号为推荐产品）|
|----|----|
|Windows | 记事本|
| | UltraEdit|
| | Visual Studio Code\*|
|MacOS | 文本编辑|
| | Sublime Text|
| | Visual Studio Code\*|
|Linux | GEdit|
| | Emacs|
| | Vim|
| | Visual Studio Code\*|
|其他 | 纸和笔|

> 是的，纸和笔也是文本编辑工具，甚至在某些情况下是唯一的文本编辑工具（考试的时候）一定要熟练掌握

> 其实就是推荐大家使用 Visual Studio Code(以下简称 VSCode)，因为真香

### 编译器

编译器基本上也有很多选择
|平台|实例|
|----|----|
|Windows | MinGW|
| | MSVC|
|MacOS | gcc|
| | clang + llvm|
|Linux | gcc|
| | clang + llvm|

**MinGW**

[MinGW](https://www.mingw-w64.org/downloads/)
MinGW (Minimalist GNU For Windows)是个精简的 Windows 平台 C/C++、ADA 及 Fortran 编译器，相比 Cygwin 而言，体积要小很多，使用较为方便。

**Visual Studio(MSVC)**

[Visual Studio](https://visualstudio.microsoft.com/zh-hans/)
不同于 Visual Studio Code，Visual Studio 是集成的开发平台，因此自带 MSVC 编译器。
Visual Studio 也自带项目管理和代码编辑器

**Apple Clang**

Clang 是一个由 Apple 主导编写，基于 LLVM 的 C/C++/Objective-C 编译器

**GCC**

[GCC](https://gcc.gnu.org)是由 GNU 开发的编程语言译器。GNU 编译器套件包括 C、C++、 Objective-C、 Fortran、Java、Ada 和 Go 语言前端，也包括了这些语言的库.

**WSL+gcc**

WSL(Windows Subsystem for Linux)为 Windows Linux 子系统，意图为 Windows 用户提供 Linux 终端环境。可以将其理解为与 Windows 并行的另一套操作系统，使得在 Windows 上利用 Linux 工具成为可能

> 由于WSL存在诸多潜在发生问题的可能性，不推荐无基础的同学使用WSL环境参与课程

**Virtual Machine+Linux+gcc**

可以在 Windows 上使用虚拟机程序安装 Linux 操作系统，在 Linux 操作系统下配置编译环境。
常见的虚拟机程序有

[VirtualBox(免费)](https://www.virtualbox.org)

[VMWare(交大正版)](https://vmap.sjtu.edu.cn/)

虚拟机建议安装[Ubuntu20.04 LTS](https://cn.ubuntu.com/)操作系统

### 集成开发环境 (IDE)

> 将编译器、编辑器和其他工具打包在一起，就是集成开发环境（Integrated Develop Environment, IDE）

Windows 可以安装如[DevC++](https://dev-cpp.com/)或者[CodeBlocks](https://www.codeblocks.org/)等 IDE，直接使用 IDE 进行代码编写。然而作者更加推荐 JetBrains 公司作品[CLion](https://www.jetbrains.com/clion)或者微软的[Visual Studio](https://visualstudio.microsoft.com/zh-hans/)。这两款是较为现代的 IDE。需要注意的是，CLion不自带编译器，需要另行下载。

MacOS 平台可以使用 XCode（可以从 AppStore 安装）或者[CLion](https://www.jetbrains.com/clion)进行开发。然而 XCode 除了在编写 iOS，MacOS 应用外能够提供平台有关的便利，此外并没有什么优势。具体来说，XCode 启动很慢，占用资源高。更重要的是项目管理成本很高。学习阶段的编程以大量简单程序为主，而非生产阶段的单一复杂程序。

Linux下可以直接使用包管理工具安装gcc等工具，也可以安装常见的IDE。

如果有时间精力，可以在自己的云平台上部署在线代码调试环境。[CS50](https://github.com/cs50/ide)、[Codeserver](https://github.com/cdr/code-server)甚至是[Jupyter](https://github.com/jupyter/jupyter)都可以用来编写代码，编译程序并运行。它们都是基于 Web 技术的开源 IDE 解决方案。[阿里云](https://cn.aliyun.com/product/yunxiao/devstudio)、[腾讯云](https://coding.net/)以及[GitHub](https://github.com/features/codespaces)也提供类似的收费服务，可以自行了解。

### 执行环境

为了执行编译出来的代码，需要有对应平台（Platform）/架构（Architecture）组合的执行器。之所以用**平台/架构组合**一词，是因为在同一平台下可能存在多种架构的计算机。例如 Windows 可以运行在普通的个人电脑中，也可以运行在平板电脑中。普通的个人电脑一般采用一种叫做`x86`的架构，而平板电脑大多采用`ARM`架构。为单一平台/架构编译的二进制文件一般来说无法在另一平台/架构组合执行。

一般来说，程序员在开发程序时，会尽可能让开发平台和执行平台相统一。例如在`x86`架构的计算机上开发`x86`架构的程序。不然就需要虚拟机或额外的工具来进行调试。

## 课程导向的环境设置教程

这一章节将要介绍本门课程（2021-2022-1-CS139）推荐的配置。与 IDE 解决方案相比，编辑器+编译器的方案更灵活轻便、更有利于课程作业这种小项目的开展，因此仍然推荐同学们采用这种方案。

### Windows 平台

|项目|推荐配置|
|---|---|
|编辑器|建议大家使用 [VSCode](https://code.visualstudio.com/)作为编辑器|
|编译器|VirtualBox虚拟机 在虚拟机中安装Linux系统并配置编译工具|

### MacOS 平台

|项目|推荐配置|
|---|---|
|编辑器|[VSCode](https://code.visualstudio.com/)|
|编译器|Apple Clang (XCode CommandLine Tools 附带)|

### Linux 平台

虚拟机、原生 Linux，在这些 Linux 平台上配置代码开发的过程随着 Linux 发行版的不同有一定区别。

|项目|推荐配置|
|---|---|
|编辑器|[VSCode](https://code.visualstudio.com/)|
|编译器|GCC (通过包管理程序安装)|

关于如何在 Linux 上配置编译工具，最简单的方法是通过各个发行版的包管理工具。

### 小结

首先，需要设置编译工具链，也就是产生可运行二进制的工具：

- 如果你原来在自己的设备上使用Linux操作系统，那么你需要参考Linux平台上设置编译工具链的有关教程。
- 如果你原来在自己的设备上使用MacOS操作系统，那么你需要安装XCode CommandLine Tools。
- 如果你原来在自己的设备上使用Windows操作系统，那么你需要安装虚拟化软件VirtualBox运行Linux系统，然后参考Linux平台上设置编译工具链的有关教程。

其次，需要安装代码编辑软件/调试工具：

- 对于任何平台，目前都推荐使用VSCode + 插件组合。这不仅高效，更已经成为了大厂的内部事实标准

## 配置编译工具

本章节描述了在各类平台上配置编译工具的大致步骤。

### 在 Windows 上设置 虚拟机

推荐使用VirtualBox虚拟化平台。可以从[VirualBox官网](https://www.virtualbox.org/)下载该软件安装。安装好VirtualBox后，就可以利用VirtualBox运行Linux操作系统。推荐使用Ubuntu 20.04 LTS 作为操作系统。关于如何安装配置 Ubuntu20.04 虚拟机，由于其篇幅较长，故记载在另一篇文档 [How to setup VirtualBox on Windows]()

之后的步骤就如同在Ubuntu20.04 LTS配置环境相同。

### 在 Mac 上安装 XCode CommandLine Tools

首先在App Store中搜索并安装XCode。然后在Mac的Terminal中执行：

```bash
xcode-select --install
```

这样安装的是 Clang+LLVM 工具。该工具同时会将系统的`gcc`命令连接到 Clang 工具下，即命令`gcc`实际在使用 clang 工具。

如果有特别需求，可以通过`brew`安装真正的 GCC 工具

### 在 Ubuntu20.04 上设置编译工具(适用于原生Linux/虚拟Linux)

在Linux上，终端是很好的与计算机交互的工具。终端是什么这个问题，[命令行界面 (CLI)、终端 (Terminal)、Shell、TTY的区别](https://www.cnblogs.com/sddai/p/9769086.html)这篇文章讲的很清楚。简而言之，终端是一种帮助用户控制计算机的工具。这个工具接收的是用户的文本命令，而非鼠标点击。其反馈是文字，而非图形。

包管理是Linux的优秀特性之一。包管理软件帮助用户快速安装软件包。

我们的课程需要用到`gcc`和`cmake`这两样工具，为了安装这两样工具，我们需要在终端中键入如下命令

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake gdb
```

在执行过程中，可能会需要输入密码。请注意密码输入后不会有提示，直接输入即可。

解释：

`sudo`命令可以使普通用户执行一些管理员权限的命令，这里`apt-get`命令需要管理员权限才能执行。`apt-get`是Ubuntu中的软件包管理器。`update`选项命令管理器更新软件包索引。`install`选项令管理器安装`build-essential`和`cmake`两个软件包。`build-essential`包括了gcc编译器等一系列的编译工具。

命令执行成功后，gcc编译工具就已经安装好了。这时候可以用`gcc --version`查看gcc版本

## Shell 环境

在本门课程中，许多操作需要在Shell环境中执行。关于Shell环境的介绍，请阅读[Introduction to Shell](introduction-to-shell/README.md)一文

## 配置 Visual Studio Code 调试环境

在配置好编译工具后，我应该如何开始使用VSCode？见另一篇指南：[Introduction to VSCode](introduction-to-vscode/README.md)

## 组织一个C语言项目

我应该如何搭建起一份课程作业的框架？见另一篇指南：[Compiling C Projects](compiling-c-projects/README.md)

## 调试C程序

我的程序出现了Bug/内存泄漏，我应该如何排除故障？见另外的指南：[Introduction to GDB](introduction-to-gdb/README.md)、[Introduction to Valgrind](introduction-to-valgrind/README.md)
