#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MSGSIZE 16

int main(int argc, char *argv[])
{
    // pingpong
    /*
        1. Use pipe to create a pipe.
        2. Use fork to create a child.
        3. Use read to read from the pipe, and write to write to the pipe.
        4. Use getpid to find the process ID of the calling process.
        5. Add the program to UPROGS in Makefile.
        6. User programs on xv6 have a limited set of library functions available to them.
        You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c,
        user/printf.c, and user/umalloc.c.
     */
    int p[2];
    pipe(p);
    printf("pipe[0]: %d, pipe[1]: %d", p[0], p[1]);
    char buf[MSGSIZE];
    int f = fork();
    if (f > 0)
    {
        printf("i am father");
        write(p, "ping", MSGSIZE);
        wait(NULL);
        read(p[0], buf, MSGSIZE);
        printf("father received %s from son\n", buf);
        printf("<%d>: received pong");
    }
    else
    {
        printf("i am son");
        read(p[0], buf, MSGSIZE);
        printf("son received %s from father\n", buf);
        printf("<%d>: received ping");
        write(p, "poing", MSGSIZE);
    }
    // if (fork() == 0)
    // {;
    //     close(0);
    //     read(0, p[0], sizeof p[0]);
    //     close(p[0]);
    //     close(p[1]);
    //     write(0,"/bin/wc", 6);
    //     getpid()
    // }
    // else
    // {
    //     close(p[0]);
    //     write(p[1], "pong\n", 12);
    //     close(p[1]);
    // }
    exit(0);
}