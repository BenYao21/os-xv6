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
    char buf[MSGSIZE];
    int f = fork(), id = getpid();
    if (f > 0)
    {
        write(p[1], "ping", MSGSIZE);
        wait(0);
        read(p[0], buf, MSGSIZE);
        printf("<%d>: received pong\n", id);
    }
    else
    {
        read(p[0], buf, MSGSIZE);
        printf("<%d>: received ping\n", id);
        write(p[1], "pong", MSGSIZE);
    }
    exit(0);
}