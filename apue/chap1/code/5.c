/**
 * 从标准输入读命令并执行
*/

#include "apue.h"
#include "error.h"
#include <sys/wait.h>

int
main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
        
        if ((pid = fork()) < 0){
            err_sys("fork error");
        }else if (pid == 0){
            execlp(buf, buf, (char *)0);
            err_ret("执行不了：%s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}