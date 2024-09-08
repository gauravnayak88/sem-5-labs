#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

int main() {
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int data[4]; // Array to store the 4 integers read from the FIFO

    printf("Consumer Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Consumer Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1) {
        res = read(pipe_fd, data, sizeof(data));
        if (res > 0) {
            printf("Consumer Process %d read: %d, %d, %d, %d\n", getpid(), data[0], data[1], data[2], data[3]);
        } else {
            fprintf(stderr, "Read error on pipe\n");
            exit(EXIT_FAILURE);
        }
        (void)close(pipe_fd);
    } else {
        exit(EXIT_FAILURE);
    }

    printf("Consumer Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}