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
void reader(char *file)
{
}

void writer(char *file)
{
}
int main(int argc, char **argv)
{
    int fd[2];
    int filed;
    int size = 5000;
    pipe(fd);
    char buffer[size];
    ssize_t read_bytes;
    ssize_t written_bytes;
    if (fork())
    {

        if (argc < 3)
        {
            fprintf(stderr, "Too few arguments\n");
            exit(1);
        }
        filed = open(argv[1], O_RDONLY);

        if (fd < 0)
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
        write(fd[1], buffer, read_bytes);
        exit(0);
    }
    read_bytes = read(fd[0], buffer, size);

    write(fd[1], buffer, read_bytes);

    if (fork())
    {
        read_bytes = read(fd[0], buffer, size);
        filed = open(argv[2], O_WRONLY);
        written_bytes = write(filed, buffer, read_bytes);
        if (written_bytes != read_bytes)
        {
            fprintf(stderr, "Cannot write\n");
            exit(1);
        }
        close(filed);
        exit(0);
    }

    printf("%s", buffer);
}
