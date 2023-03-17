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
    printf("uuuu");
    int rtosfd;
    int size = 5000;
    int filed;
    char buffer[size];
    printf("uuuu");
    char *rtosfifo = "reader_to_solve_fifo";
    char *stowfifo = "solve_to_writer_fifo";
    int stowfd;
    ssize_t read_bytes;
    ssize_t written_bytes;

    mkfifo(rtosfifo, 0010);
    mkfifo(stowfifo, 0011);
    printf("uuuu");
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

    int res[2];
    read_bytes = read(stowfd, buffer, size);
    close(stowfd);
    filed = open(argv[2], O_WRONLY);

    memcpy(res, buffer, read_bytes);
    sprintf(buffer, "%d", res[0]);
    sprintf(&buffer[sizeof(int)], "%d", res[1]);

    written_bytes = write(filed, buffer, read_bytes);

    if (written_bytes != read_bytes)
    {
        fprintf(stderr, "Cannot write\n");
        exit(1);
    }

    close(filed);
    exit(0);
}