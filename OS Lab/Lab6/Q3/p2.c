#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 4

int main() {
    int pipe_fd;
    int res;
    int data_to_write[] = {50, 60, 70, 80}; // Second program's data
    int data_to_read[BUFFER_SIZE];          // Buffer to read data
    int size = sizeof(data_to_write);

    while (1) {
        // First, read from FIFO
        printf("Second Program Process %d waiting to read from FIFO\n", getpid());
        pipe_fd = open(FIFO_NAME, O_RDONLY);
        if (pipe_fd != -1) {
            res = read(pipe_fd, data_to_read, size);
            if (res > 0) {
                printf("Second Program Process %d read: %d, %d, %d, %d\n",
                       getpid(), data_to_read[0], data_to_read[1],
                       data_to_read[2], data_to_read[3]);
            } else {
                fprintf(stderr, "Read error on pipe\n");
                exit(EXIT_FAILURE);
            }
            (void)close(pipe_fd);
        } else {
            exit(EXIT_FAILURE);
        }

        // Then, write to FIFO
        printf("Second Program Process %d writing to FIFO\n", getpid());
        pipe_fd = open(FIFO_NAME, O_WRONLY);
        if (pipe_fd != -1) {
            res = write(pipe_fd, data_to_write, size);
            if (res == -1) {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
            else {
            	for (int i=0; i<BUFFER_SIZE; i++) {
                    data_to_write[i]+=10;
                }
            }
            (void)close(pipe_fd);
        } else {
            exit(EXIT_FAILURE);
        }
        sleep(1); // Delay to alternate between the programs
    }

    exit(EXIT_SUCCESS);
}
