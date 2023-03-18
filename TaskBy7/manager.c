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
    int rtosfd;
    int stowfd;
    int rtosfd1;
    int stowfd1;
    char *rtosfifo = "reader_to_solve_fifo";
    char *stowfifo = "solve_to_writer_fifo";
    mkfifo(rtosfifo, 0777);
    mkfifo(stowfifo, 0777);
    rtosfd = open(rtosfifo, O_RDONLY);
    stowfd = open(stowfifo, O_WRONLY);
    rtosfd1 = open(rtosfifo, O_WRONLY);
    stowfd1 = open(stowfifo, O_RDONLY);
    dup2(rtosfd, 10);
    dup2(stowfd, 21);
    dup2(rtosfd1, 11);
    dup2(stowfd1, 20);
    close(rtosfd);
    close(stowfd);
    close(rtosfd1);
    close(stowfd1);
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
        execv("./reader.o", argv);
    }
    return 0;
}
