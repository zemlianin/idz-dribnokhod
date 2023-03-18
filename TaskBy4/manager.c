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
    int fd[2];
    int fdw[2];
    int size = 5000;
    pipe(fd);
    pipe(fdw);
    dup2(fd[0], 10);
    dup2(fd[1], 11);
    dup2(fdw[0], 20);
    dup2(fdw[1], 21);
    char buffer[size];
    ssize_t read_bytes;

    if (fork())
    {
        execv("./reader.o", argv);
    }
    if (fork())
    {
        execv("./solve.o", argv);
    }
    if (fork())
    {
        execv("./writer.o", argv);
    }

    close(fd[0]);
    close(fd[1]);
    close(10);
    close(11);
    close(fdw[0]);
    close(fdw[1]);
    close(20);
    close(21);
}
