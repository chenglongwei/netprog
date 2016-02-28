#include <unistd.h>
#include <stdio.h>

void print_counter(char*);

int main() {
    int i = 0;
    char process_name[50];
    for (i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            // fork error.
            return fork_error(pid);
        }
        if (pid == 0) {
            // child
            sprintf(process_name, "child%d", i);
            print_counter(process_name);
            return 0;
        }
    }
    
    print_counter("parent");
    return 0;
}

int fork_error(int error_code) {
    printf("fork error: %d\n", error_code);
    return error_code;
}

void print_counter(char* process_name) {
    int i = 0;    	
    for (i = 0; i < 5; i++) {
        printf("process %s, counter %d\n", process_name, i);
        sleep(1);
    }
}
