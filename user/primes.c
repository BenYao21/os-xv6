#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    for (int i = 2; i < 36; i++)
    {
        int cur = 2;
        if (cur == i)
        {
            printf("prime %d", i);
        }
        else
        {
            if (i % cur == 0)
            {
                exit(0);
            }
            else
            {
                int nxt = cur + 1;
                write(p[1], nxt, sizeof p[1]);
                int fid = fork();
            }
        }
    }
    exit(0);
}