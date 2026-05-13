#include <stdio.h>
#include <stdlib.h>

int main() {
    char *num1_str = getenv("NUM1");
    char *num2_str = getenv("NUM2");
    char *num3_str = getenv("NUM3");

    if (num1_str == NULL || num2_str == NULL || num3_str == NULL) {
        fprintf(stderr, "Error: Environment variables NUM1, NUM2, and NUM3 must be set.\n");
        return 1;
    }

    double num1 = atof(num1_str);
    double num2 = atof(num2_str);
    double num3 = atof(num3_str);

    double mean = (num1 + num2 + num3) / 3.0;
    printf("Mean: %.2f\n", mean);
    return 0;
}
