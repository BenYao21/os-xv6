#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MSGSIZE 36
#define ZERO '0'
#define ONE '1'

void prime(int pipe_read, int pipe_write)
{
    char buf[MSGSIZE];
    int val = 0;
    read(pipe_read, buf, MSGSIZE);
    for (int i = 2; i < MSGSIZE; i++)
    {
        if (buf[i] == ONE)
        {
            val = i;
            break;
        }
    }
    if (val == 0)
    {
        exit(0);
    }
    printf("prime %d\n", val);
    buf[val] = ZERO;
    int raw = val;
    val += raw;
    while (val < MSGSIZE)
    {
        buf[val] = ZERO;
        val += raw;
    }
    int pid = fork();
    if (pid > 0) // child node
    {
        write(pipe_write, buf, MSGSIZE);
    }
    if (pid == 0) // grandchild node
    {
        prime(pipe_read, pipe_write);
    }
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    char nums[MSGSIZE];

    for (int i = 2; i < MSGSIZE; i++)
    {
        nums[i] = ONE;
    }
    int pid = fork();
    if (pid > 0)
    {
        nums[0] = ZERO;
        nums[1] = ZERO;
        write(fd[1], nums, MSGSIZE);
        wait(0);
    }

    if (pid == 0)
    {
        prime(fd[0], fd[1]);
        wait(0);
    }
    exit(0);
}
