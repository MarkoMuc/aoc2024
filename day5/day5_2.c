#include "../includes/aoc.h"
#include <stdbool.h>
#include <stdlib.h>

#define _TEST_FILE_ "./case.in"
//#define _TEST_FILE_ "./case.test"

#define BEFORE 1
#define AFTER 2
#define MAX_ARR_ROW 100
#define MAX_ARR_COL 100

long order_correctly(int **rules, int *nums, int size) {
    for(int i = 0; i < size; i++){
        int X = nums[i];
        for(int j = i + 1; j < size; j ++) {
            if(i == j) continue;
            int Y = nums[j];
            if((j<i && rules[Y][X] == AFTER) ||
                (i<j && rules[Y][X] == BEFORE)){
                nums[i] = Y;
                nums[j] = X;
                i = -1;
                break;
            }
        }
    }

    return nums[size/2];
}

long calculate(int **rules, int *nums, int size) {
    for(int i = 0; i < size; i++){
        int X = nums[i];
        for(int j = i+1; j < size; j ++) {
            if(i == j) continue;
            int Y = nums[j];
            if((j<i && rules[Y][X] == AFTER) ||
                (i<j && rules[Y][X] == BEFORE)){
                return order_correctly(rules, nums, size);
            }
        }
    }

    return 0;
}

int main() {
    FILE *f = fopen(_TEST_FILE_, "r");
    size_t size = 0;
    int read;
    char* line = NULL;
    bool rules = true;
    long sum = 0;

    int **r_arr = aoc_num_matrix(MAX_ARR_ROW, MAX_ARR_COL);

    size_t n_size = MAX_ARR_COL;
    int *n_arr;

    while((read = aoc_read_newline(f, &line, &size)) > 0) {
        if(read <= 1) { 
            rules = false;
            continue;
        }
        size_t idx = 0;
        if(rules) {
            int X = aoc_get_num(line, read, &idx);
            idx++;
            int Y = aoc_get_num(line, read, &idx);
            r_arr[X][Y] = BEFORE;
            r_arr[Y][X] = AFTER;
        }else{
            int i = aoc_line_to_nums(line, read, &n_arr, &n_size, 1);
            sum += calculate(r_arr, n_arr, i);
        }
    }

    printf("%ld\n", sum);

    fclose(f);
    aoc_free_matrix(r_arr, MAX_ARR_COL);
    free(line);
    free(n_arr);
    exit(0);
}
