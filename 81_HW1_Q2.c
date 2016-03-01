#include <unistd.h>
#include <stdio.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        printf("fork error, %d", pid);
        return pid;
    }

    char *envp[] = {NULL};
    char *argv[] = {"./sum"};

    if (pid > 0) {
        // child process
        execve("sum", argv, envp);
    }

    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("counter: %d\n", i);
    }
}
