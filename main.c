#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#define INDEX_MAX (100*1000*1000)
// Plotting every single floating point number would bloat the
// data file way too much. Let's only plot every floating point
// number in steps of INDEX_STEP.
#define INDEX_STEP (100*1000)

int main(void) {
    FILE* file = fopen("data.txt", "w");
    if (!file) {
        perror("Failed to open 'data.txt' for writing");
        exit(EXIT_FAILURE);
    }

    // Plotting positive numbers
    int index = 0;
    float current = 0.0f;
    while(index <= INDEX_MAX && current != HUGE_VALF) {
        bool should_print = index % INDEX_STEP == 0;
        if (should_print && fprintf(file, "%d %.*g\n", index, FLT_DECIMAL_DIG, current) < 0) {
            perror("Failed to write to 'data.txt'");
            exit(EXIT_FAILURE);
        }
        current = nextafterf(current, FLT_MAX);
        index += 1;
    }

    // Plotting negative numbers
    index = 0;
    current = 0.0f;
    while(index <= INDEX_MAX && current != HUGE_VALF) {
        bool should_print = index % INDEX_STEP == 0;
        if (should_print && fprintf(file, "-%d %.*g\n", index, FLT_DECIMAL_DIG, current) < 0) {
            perror("Failed to write to 'data.txt'");
            exit(EXIT_FAILURE);
        }
        current = nextafterf(current, -FLT_MAX);
        index += 1;
    }

    exit(EXIT_SUCCESS);
}
