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

void solve(char *str, int size, int *res)
{
    int ps = 0;
    int ss = 0;
    for (size_t i = 0; i < size; i++)
    {
        if ('A' <= str[i] && 'Z' >= str[i])
        {
            ps++;
        }
        if ('a' <= str[i] && 'z' >= str[i])
        {
            ss++;
        }
    }
    res[0] = ps;
    res[1] = ss;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Too few arguments\n");

        exit(1);
    }
    int rtosfd;
    int stowfd;
    int rtosfd1;
    int stowfd1;
    char *rtosfifo = "reader_to_solve_fifo";
    char *stowfifo = "solve_to_writer_fifo";
    mkfifo(rtosfifo, 0010);
    mkfifo(stowfifo, 0011);
    rtosfd = open(rtosfifo, O_WRONLY);
    stowfd = open(stowfifo, O_WRONLY);
    rtosfd1 = open(rtosfifo, O_RDONLY);
    stowfd1 = open(stowfifo, O_RDONLY);
    dup2(rtosfd, 11);
    dup2(rtosfd1, 10);
    dup2(stowfd, 21);
    dup2(stowfd1, 20);
    close(stowfd);
    close(stowfd1);
    close(rtosfd1);
    close(rtosfd);

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
}
