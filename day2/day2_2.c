#include "../includes/aoc.h"
#include <stdio.h>
#include <stdlib.h>

int get_num(char *line, size_t len, size_t *start) {
    int idx = *start;
    int num = 0;
    if(*start >= len - 1) {
        return -1;
    }

    for(; idx < len; idx++) {
        if(line[idx] >= '0' && line[idx] <= '9'){
            num = num * 10 + (line[idx] - '0');
        }else{
            idx++;
            break;
        }
    }

    *start = idx;
    return num;
}

int main() {
    FILE *f = fopen("./case.in", "r");
    char* line = NULL;
    size_t size = 0;
    int read;

    int correct_lines = 0;
    long array_size = 256;
    int *array = malloc(array_size*sizeof(int));

    while((read = aoc_read_newline(f, &line, &size)) > 0) {
        size_t start = 0;
        int i = 0;

        while(1){
            int num = get_num(line, read, &start);
            if(num == -1){
                break;
            }
            if(i >= array_size) {
                array_size = array_size * 2;
                array = realloc(array, array_size *sizeof(int));
            }else{
                array[i] = num;
            }
            i++;
        }

        int replace_idx = 0;
        int replaced_num = -1;
        int replaced_count = 0;

        int correct = 1;
        int asc = -1;

        for(int idx = 0; idx < i - 1; idx++) {
            int num1;
            int num2;

            if(replaced_count > i) {
                correct = 0;
                break;
            }

            if(replaced_num != -1 && replace_idx == idx){
                idx++;
            }

            num1 = array[idx];

            if(idx+1 >= i || (replace_idx == idx+1 && replace_idx+1 >= i)){
                break;
            }

            if(replace_idx == idx+1){
                num2 = array[idx+2];
            }else{
                num2 = array[idx+1];
            }

            int diff = num2 - num1;

            if(abs(diff) < 1 || abs(diff) > 3) {
                if(replaced_num != -1) {
                    array[replace_idx] = replaced_num;
                    replace_idx++;
                }
                replaced_num = array[replace_idx];
                replaced_count++;
                asc = -1;
                idx = -1;
                continue;
            }

            if(asc == -1) {
                asc = diff < 0 ? 0: 1;
            }

            if((diff > 0 && !asc) || (diff < 0 && asc)){
                if(replaced_num != -1) {
                    array[replace_idx] = replaced_num;
                    replace_idx++;
                }
                replaced_num = array[replace_idx];
                replaced_count++;
                asc = -1;
                idx = -1;
                continue;
            }
        }

        if(correct == 1) {
            correct_lines++;
        }
    }

    printf("%d\n", correct_lines);

    fclose(f);
    free(line);
    exit(0);
}
