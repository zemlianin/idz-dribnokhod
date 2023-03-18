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
    char *rtosfifo = "reader_to_solve_fifo";
    char *stowfifo = "solve_to_writer_fifo";

    if (mkfifo(rtosfifo, 0777))
    {
        perror("mkfifo");
        return 1;
    }

    if (mkfifo(stowfifo, 0777))
    {
        perror("mkfifo");
        return 1;
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
