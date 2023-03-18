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
    int rtosfd;
    char *rtosfifo = "reader_to_solve_fifo";
    int size = 5000;
    int filed;
    char buffer[size];
    ssize_t read_bytes;
    char *stowfifo = "solve_to_writer_fifo";
    int stowfd;
    ssize_t written_bytes;
    int res[2];

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

    while ((rtosfd = open(rtosfifo, O_WRONLY)) == -1)
    {
        fprintf(stdout, "Процесс чтения ожидает создания канала\n");
        sleep(5);
    }
    write(rtosfd, buffer, read_bytes);
    close(rtosfd);
    while ((stowfd = open(stowfifo, O_RDONLY)) == -1)
    {
        fprintf(stdout, "Процесс чтения ожидает создания канала\n");
        sleep(5);
    }

    read_bytes = read(stowfd, buffer, size);

    close(stowfd);
    remove(stowfifo);
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