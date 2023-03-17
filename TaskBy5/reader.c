#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void sys_err(char *msg)
{
    puts(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments\n");

        exit(1);
    }
    int rtosfd;
    char *rtosfifo = "reader_to_solve_fifo";
    int size = 5000;
    int filed;
    char buffer[size];
    ssize_t read_bytes;

    mkfifo(rtosfifo, 0010);

    filed = open(argv[1], O_RDONLY);

    if (filed < 0)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }

    read_bytes = read(filed, buffer, size);

    if (read_bytes < 0)
    {
        fprintf(stderr, "myread: Cannot read file\n");
        exit(1);
    }

    close(filed);
    rtosfd = open(rtosfifo, O_WRONLY);
    write(rtosfd, buffer, read_bytes);
    close(rtosfd);
    return 0;
}