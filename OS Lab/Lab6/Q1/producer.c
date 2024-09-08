#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

int main() {
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int data[] = {10, 20, 30, 40}; // Set of 4 integers to write
    int size = sizeof(data);

    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    printf("Producer Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Producer Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        res = write(pipe_fd, data, size);
        if (res == -1) {
            fprintf(stderr, "Write error on pipe\n");
            exit(EXIT_FAILURE);
        }
        else
            printf("Producer Process %d wrote: %d, %d, %d, %d\n", getpid(), data[0], data[1], data[2], data[3]);
        (void)close(pipe_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Producer Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
