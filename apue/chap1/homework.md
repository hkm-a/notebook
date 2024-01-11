## 在系统上验证，除根目录外，目录.和..是不同的。
```
ls --help
Usage: ls [OPTION]... [FILE]...
List information about the FILEs (the current directory by default).

  -d, --directory            list directories themselves, not their contents
  
  -i, --inode                print the index number of each file
  
  -l                         use a long listing format
```

```bash
ls -ldi
```
主要是`-i`保证唯一性
## 分析图1-6程序的输出，说明进程ID为852和853的进程发生了什么情况？
```
/**
 * 打印进程ID
*/

#include "apue.h"
int 
main(void)
{
    printf("hello world from process ID %ld\n", (long)getpid());
    exit(0);
}
```
UNIX系统是多道程序或多任务系统，所以，在图1-6所示程序运行的同时其他两个进程也在运行。
## 在1.7节中，perror的参数是用ISO C的属性const定义的，而strerror的整型参数没有用此属性定义，为什么？
```
char *strerror(int errnum);

void perror(const char *msg);
```
因为perror的msg参数是一个指针，perror就可以改变msg指向的字符串。然而使用限定符const限制了perror不能修改msg指针指向的字符串。而对于strerror，其错误号参数是整数类型，并且C是按值传递所有参数，因此即使strerror函数想修改参数的值也修改不了，也就没有必要使用const属性。
## 若日历时间存放在带符号的32位整型数中，那么到哪一年它将溢出？可以用什么方法扩展溢出浮点数？采用的策略是否与现有的应用相兼容？
```2^31天```
在2038年。将time_t数据类型定为64位整型，就可以解决该问题了。如果它现在是32位整型，那么为使应用程序正常工作，应当对其重编译。但是这一问题还有更糟糕之处。

某些文件系统及备份介质以32位整型存放时间。对于这些同样需要加以更新，但又需要能读旧的格式。
## 若进程时间存放在带符号的32位整型数中，而且每秒为100时钟滴答，那么经过多少天后该时间值将会溢出?
大约```248```天
```python
print(2**31/100/60/60/24)
```