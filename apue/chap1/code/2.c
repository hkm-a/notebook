/**
 * 将标准输入复制到标准输出
*/

#include "apue.h"
#include "error.h"
#define BUFFSIZE 4096

int
main(void)
{
    int n;
    char buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("写错误");
    if (n < 0)
        err_sys("读错误");

    exit(0);    
}