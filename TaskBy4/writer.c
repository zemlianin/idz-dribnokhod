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
    int size = 5000;
    int filed;
    char buffer[size];
    ssize_t read_bytes;
    ssize_t written_bytes;
    int res[2];
    read_bytes = read(10, buffer, size);
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