# APUE 第 1 章 - UNIX 基础知识

## 1. UNIX 历史

UNIX 操作系统诞生于 1969 年,由贝尔实验室的 Ken Thompson 和 Dennis Ritchie 开发。UNIX 最初在 PDP-7 微型计算机上实现,随后被移植到其他硬件平台。UNIX 的设计理念包括:

1. 一切皆文件:UNIX 将所有资源都视为文件,包括硬件设备、进程等。
2. 软件工具的模块化设计:UNIX 提供了许多小巧且功能单一的工具,可以灵活组合使用。
3. 支持多用户和多任务:UNIX 系统支持多用户同时使用,并能够并发执行多个任务。

UNIX 的发展历程经历了 AT&T UNIX、BSD UNIX、System V UNIX 等多个版本,最终演化出现代的 Linux 操作系统。

## 2. UNIX 系统组成

UNIX 系统主要由以下四个部分组成:

1. 内核(Kernel):负责管理硬件资源、进程调度和内存管理等底层功能。
2. Shell:命令解释器,负责接受用户命令并执行相应的程序。
3. 系统实用程序:提供各种功能性工具,如文件管理、网络通信等。
4. 应用程序:为用户提供各种服务,如文字处理、图形编辑等。

## 3. UNIX 系统调用

UNIX 系统提供了许多系统调用,供程序员在编写应用程序时使用。这些系统调用可以分为以下几个主要类别:

1. 文件 I/O 相关:open、read、write、close 等。
2. 进程控制:fork、exec、wait 等。
3. 信号处理:signal、kill 等。
4. 其他系统资源管理:chmod、stat 等。

让我们看一个简单的示例程序,演示如何使用 `printf` 和 `return` 系统调用:

```c
#include <stdio.h>

int main() {
    printf("Hello, UNIX!\n");
    return 0;
}
```

在这个程序中,我们使用了 `printf` 函数打印输出 "Hello, UNIX!"。最后,我们使用 `return` 系统调用返回状态码 0,表示程序执行成功。

## 4. UNIX 文件系统

UNIX 文件系统有以下几个重要特性:

1. 层级目录结构:文件和目录组成了一个树状的层级结构。
2. 文件类型:UNIX 支持多种文件类型,包括普通文件、目录、设备文件等。
3. 文件访问权限:每个文件都有读、写、执行的权限控制。
4. 文件所有者和组:每个文件都有一个所有者和所属组。
5. 文件时间戳:包括访问时间、修改时间和状态改变时间。

下面是一个示例程序,演示如何使用 `stat` 系统调用获取文件的元数据信息:

```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat sb;
    if (stat("./main.c", &sb) == -1) {
        perror("stat");
        return 1;
    }

    printf("File type: ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFREG:  printf("regular file\n");  break;
        case S_IFDIR:  printf("directory\n");     break;
        case S_IFCHR:  printf("character device\n");  break;
        case S_IFBLK:  printf("block device\n");  break;
        case S_IFLNK:  printf("symbolic link\n"); break;
        case S_IFIFO:  printf("FIFO\n");          break;
        case S_IFSOCK: printf("socket\n");        break;
        default:       printf("unknown?\n");      break;
    }

    return 0;
}
```

在这个程序中,我们使用 `stat` 系统调用获取文件 `main.c` 的元数据信息,并根据文件类型打印出相应的描述。

## 5. UNIX 进程

UNIX 进程有以下四个主要概念:

1. 进程创建:使用 `fork` 系统调用创建子进程。
2. 程序执行:使用 `exec` 系统调用执行新的程序。
3. 进程终止:进程可以主动调用 `exit` 系统调用退出,也可以被其他进程终止。
4. 进程间通信:进程可以通过管道、信号等机制进行通信。

下面是一个示例程序,演示如何创建子进程:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    printf("Before fork\n");
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Child process (PID: %d)\n", getpid());
    } else {
        printf("Parent process (PID: %d, Child PID: %d)\n", getpid(), pid);
    }
    printf("After fork\n");
    return 0;
}
```

在这个程序中,我们首先使用 `fork` 系统调用创建了一个子进程。在子进程中,`pid` 会返回 0,而在父进程中,`pid` 会返回子进程的 ID。最后,我们在父进程和子进程中分别打印了相应的进程 ID 信息。

## 6. UNIX 信号

UNIX 信号机制有以下四个重要概念:

1. 信号类型:UNIX 系统定义了多种信号,如 `SIGINT`(Ctrl+C)、`SIGKILL`(强制终止)等。
2. 信号的发送和处理:进程可以向其他进程发送信号,接收进程可以选择忽略或处理这些信号。
3. 信号处理函数:进程可以注册自定义的信号处理函数,在收到信号时执行相应的操作。
4. 信号集合的管理:进程可以使用 `sigset_t` 类型管理自己的信号集合。

下面是一个示例程序,演示如何注册自定义的信号处理函数:

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    printf("Received signal: %d\n", signo);
}

int main() {
    signal(SIGINT, signal_handler);
    printf("Press Ctrl+C to send SIGINT signal\n");
    while (1) {
        pause();
    }
    return 0;
}
```

在这个程序中,我们使用 `signal` 系统调用注册了一个自定义的信号处理函数 `signal_handler`。当程序收到 `SIGINT` 信号(通常由 Ctrl+C 触发)时,会执行这个处理函数并打印信号编号。
