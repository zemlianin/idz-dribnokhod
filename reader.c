#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

void sys_err(char *msg)
{
    puts(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    int fd;
    int size = 5000 char buffer[size + 1];
    ssize_t read_bytes;
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }
    read_bytes = read(fd, buffer, size) if (read_bytes < 0)
    {
        fprintf(stderr, "myread: Cannot read file\n");
        exit(1);
    }
    close(fd);

    int shm_id, shm_id_finish;
    int *share, *share_resp_code;
    int num;

    shm_id = shmget(0x2FF, sizeof(int), 0666 | IPC_CREAT);
    shm_id_finish = shmget(0x2FA, sizeof(int), 0666 | IPC_CREAT);

    share = (int *)shmat(shm_id, 0, 0);
    share_resp_code = (int *)shmat(shm_id_finish, 0, 0);

    for (int i = 0; i < count; ++i)
    {
        num = random() % 1000;
        *share = num;
        *share_resp_code = 0;
        printf("random num in buffer: %d\n", num);
        while (*share_resp_code != 200)
        {
            sleep(1);
        }
    }
    *share_resp_code = -1;
    shmdt(share);
    shmdt(share_resp_code);
    if (shmctl(shm_id, IPC_RMID, (struct shmid_ds *)0) < 0)
    {
        sys_err("eraser: shared memory remove error");
    }
    else if (shmctl(shm_id_finish, IPC_RMID, (struct shmid_ds *)0) < 0)
    {
        sys_err("eraser: shared memory remove error");
    }

    printf("eraser: shared memory using key = %x deleted\n", 0x2FF);
    printf("eraser: shared memory using key = %x deleted\n", 0x2FA);
    return 0;
}