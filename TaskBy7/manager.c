#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void sys_err(char *msg)
{
    puts(msg);
    exit(1);
}

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        fprintf(stderr, "Too few arguments\n");

        exit(1);
    }

    if (fork())
    {
        execv("./solve.o", argv);
    }
    if (fork())
    {
        printf("uuuu");
        execv("./reader.o", argv);
    }
    return 0;
}
