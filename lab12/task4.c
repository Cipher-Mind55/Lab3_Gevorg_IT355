#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sleep_time1> <sleep_time2> ...\n", argv[0]);
        return 1;
    }

    int num_children = argc - 1;

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            int sleep_time = atoi(argv[i]);
            sleep(sleep_time);
            printf("Child process (PID %d) suspended for %d seconds has finished.\n", getpid(), sleep_time);
            return 0; // The child must exit after finishing its job
        }
    }

    // Parent process waits for all children
    int completed = 0;
    for (int i = 0; i < num_children; i++) {
        pid_t finished_pid = wait(NULL);
        if (finished_pid > 0) {
            completed++;
            printf("Parent process: Child with PID %d has finished. Total completed: %d\n", finished_pid, completed);
        }
    }

    printf("Parent process ending.\n");
    return 0;
}
