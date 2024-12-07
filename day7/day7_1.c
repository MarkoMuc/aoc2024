#include "../includes/aoc.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _TEST_FILE_ "./case.in"
//#define _TEST_FILE_ "./case.test"

#define MAX_ROWS 850
typedef unsigned __int128 uint128_t;

typedef struct {
    uint128_t size;
    uint128_t count;
    uint128_t *el;
} dyarr;

void dyarr_init(dyarr *arr){
    arr->size = 256;
    arr->count = 0;
    arr->el = malloc(arr->size * sizeof(*(arr->el)));
}

void dyarr_add(dyarr *arr, uint128_t element){
    if(arr->count >= arr->size) {
        arr->size = arr->size * 2;
        arr->el = realloc(arr->el, arr->size * sizeof(*(arr->el)));
    }
    arr->el[arr->count] = element;
    arr->count = arr->count + 1;
}

uint128_t dyarr_get(dyarr *arr, uint128_t idx){
    if(idx >= arr->count) {
        return -1;
    }
    return arr->el[idx];
}

bool express(uint128_t res, dyarr *arr, uint128_t idx, uint128_t curr){
    if(idx > arr->count){
        return false;
    }

    if(curr > res){
        return false;
    }

    if(idx == arr->count){
        return curr == res;
    }

    uint128_t next = dyarr_get(arr, idx);

    //MUL
    if(express(res, arr, idx + 1, curr * next)){
        return true;
    }

    //ADD
    if(express(res, arr, idx + 1, curr + next)){
        return true;
    }

    return false;
}

uint128_t calibration(uint128_t *res, dyarr *eq, size_t rows){
    uint128_t sum = 0;
    for(uint128_t i = 0; i < rows; i++){
        if(express(res[i], &eq[i], 1, dyarr_get(&eq[i], 0))){
            sum += res[i];
        }
    }
    return sum;
}

void print_uint128(__uint128_t value) {
    uint64_t high = value >> 64;       // Extract high 64 bits
    uint64_t low = value & 0xFFFFFFFFFFFFFFFF; // Extract low 64 bits

    if (high > 0) {
        printf("%lu%016lu\n", high, low); // Print as two 64-bit parts
    } else {
        printf("%lu\n", low);            // Print only the lower part if high is 0
    }
}

uint128_t get_num(char *line, size_t len, size_t *start) {
    uint128_t idx = *start;
    uint128_t num = 0;
    if(*start >= len - 1) {
        return -1;
    }

    for(; idx < len; idx++) {

        if(line[idx] >= '0' && line[idx] <= '9') {
            num = num * 10 + (line[idx] - '0');
        }else {
            break;
        }
    }

    *start = idx;
    return num;
}

int main() {
    FILE *f = fopen(_TEST_FILE_, "r");
    size_t size = 0;
    char* line = NULL;
    int read;
    size_t rows = 0; 
    uint128_t *result = malloc(MAX_ROWS * sizeof(uint128_t));
    dyarr *eq = malloc(MAX_ROWS * sizeof(dyarr));

    while((read = aoc_read_newline(f, &line, &size)) > 0) {
        size_t idx = 0;
        result[rows] = get_num(line, read, &idx);
        idx += 2;
        dyarr_init(&eq[rows]);
        for(uint128_t i = 0; i < read; i ++){
            uint128_t num = get_num(line, read, &idx);
            if(num == -1){
                break;
            }
            dyarr_add(&eq[rows], num);
            idx++;
        }
        rows++;
    }

    print_uint128(calibration(result, eq, rows));

    for(int i = 0; i < rows; i++){
        free(eq[i].el);
    }
    free(eq);
    free(result);
    fclose(f);
    free(line);
    exit(0);
}
