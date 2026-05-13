#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(3);
        printf("Child process (PID %d) has finished.\n", getpid());
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process: Child with PID %d has finished. Parent process is ending.\n", pid);
    }
    return 0;
}
