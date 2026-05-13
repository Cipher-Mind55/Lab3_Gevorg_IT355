#include <stdio.h>
#include <stdlib.h>
#include "filter_func.h"

int main(int argc, char *argv[]) {
    if (argc != 11) {
        fprintf(stderr, "Error: Expected exactly 10 arguments.\n");
        return 1;
    }

    int arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int new_size = remove_odds(arr, 10);

    printf("Array after removing odd numbers: ");
    for (int i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
