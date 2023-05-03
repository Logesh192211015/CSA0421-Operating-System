#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 

int main() {
    int shmid;
    char *shm;
    char *message = "Hello, world!";

    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    strncpy(shm, message, SHM_SIZE);

    shmdt(shm);

    if (fork() == 0) {
        char *shm_child;
        if ((shm_child = shmat(shmid, NULL, 0)) == (char *) -1) {
            perror("shmat");
            exit(1);
        }

        printf("Message received: %s\n", shm_child);

        shmdt(shm_child);

        shmctl(shmid, IPC_RMID, NULL);

        exit(0);
    }
