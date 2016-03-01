#include <stdlib.h>
#include <stdio.h>

int main() {
    int i;
    int sum = 0;
    for (i = 1; i <= 5; i++) {
        printf("The value of i is %d\n", i);
        fflush(stdout);
        sum += i;
    }
    
    printf("The sum is %d\n", sum);
    exit(0);
}
