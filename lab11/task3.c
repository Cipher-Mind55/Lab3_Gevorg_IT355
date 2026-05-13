#include <stdio.h>
#include <stdlib.h>
#include "max_func.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: Expected exactly 3 arguments.\n");
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    
    int max = get_max(a, b, c);
    printf("Max: %d\n", max);
    return 0;
}
