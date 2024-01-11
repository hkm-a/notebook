/**
 * 用标准I/O将标准输入复制到标准输出
*/

#include "apue.h"
#include "error.h"
int
main(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("输出错误");
    if (ferror(stdin))
        err_sys("输入错误");
    exit(0);
}