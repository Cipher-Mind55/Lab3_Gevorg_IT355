#include "filter_func.h"

int remove_odds(int *arr, int n) {
    int new_size = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    return new_size;
}
