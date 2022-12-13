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
    for (int i = 0; i < MSGSIZE; i++)
    {
        if (buf[i] == ONE)
        {
            val = i;
            break;
        }
    }
    printf("prime %d", val);
    buf[val] = ZERO;
    int raw = val;
    val += raw;
    while (val < MSGSIZE)
    {
        buf[val] = ZERO;
        val += raw;
    }
    int pid = fork();
    if (pid > 0)
    {
        write(pipe_write, buf, MSGSIZE);
    }
    if (pid == 0)
    {
        prime(pipe_read, pipe_write);
    }
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    int pid = fork();
    char nums[MSGSIZE];
    if (pid > 0)
    {
        char nums[MSGSIZE];
        nums[0] = ZERO;
        nums[1] = ZERO;
        write(fd[1], nums, MSGSIZE);
    }

    if (pid == 0)
    {
        prime(fd[0], fd[1]);
        wait(0);
    }
    exit(0);
}
