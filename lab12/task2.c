#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: My ID is %d, my parent's ID is %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process: My ID is %d, my child's ID is %d\n", getpid(), pid);
    }
    return 0;
}
