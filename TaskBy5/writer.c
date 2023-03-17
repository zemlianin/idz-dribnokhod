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
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments\n");

        exit(1);
    }
    char *stowfifo = "solve_to_writer_fifo";
    int stowfd;
    int size = 5000;
    int filed;
    char buffer[size];
    ssize_t read_bytes;
    ssize_t written_bytes;
    int res[2];

    mkfifo(stowfifo, 0011);
    stowfd = open(stowfifo, O_RDONLY);

    read_bytes = read(stowfd, buffer, size);
    close(stowfd);
    filed = open(argv[1], O_WRONLY);

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