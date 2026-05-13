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
        char *args[] = {"ls", NULL};
        execvp("ls", args);
        // If execvp returns, it must have failed
        perror("execvp failed");
        return 1;
    } else {
        // Parent process
        wait(NULL);
        printf("Parent process: Program has finished.\n");
    }
    return 0;
}
