#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("no more than 1 integer in input");
    }
    else
    {
        uint64 t = atoi(argv[1]);
        sleep(t);
    }
    exit(0);
}