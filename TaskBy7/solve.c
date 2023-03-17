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
    int size = 5000;
    char buffer[size];
    ssize_t read_bytes;

    read_bytes = read(10, buffer, size);
    close(10);
    int res[2];
    solve(buffer, read_bytes, res);
    memcpy(buffer, res, 2 * sizeof(int));

    write(21, buffer, 2 * sizeof(int));
    close(21);
    return 0;
}
