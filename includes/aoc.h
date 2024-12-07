#include <stdio.h>
#include <stdlib.h>

#define __DEFAULT__LINE__SIZE__ 256

#define aoc_free_matrix(mtrx, row) \
    do{ \
        for(int i = 0; i < (row); i++) free((mtrx)[i]);\
        free((mtrx));\
    }while(0)

int aoc_read_newline(FILE *f, char** line, size_t *size) {
    size_t line_size = *size;
    long line_len = 0;

    if(f == NULL){
        printf("File not opened.\n");
        exit(1);
    }

    if(*line != NULL && line_size == 0) {
        printf("Line allocated but line len is set to 0.\n");
        exit(1);
    }

    if(*line == NULL) {
        line_size = line_size > 0? line_size: __DEFAULT__LINE__SIZE__;
        *size = line_size;
        *line = malloc(line_size * sizeof(**line));
        if(*line == NULL) {
            printf("Failed to allocate to size %u", line_size);
            exit(0);
        }
    }

    int read;
    size_t line_offset = 0;
    size_t read_size = line_size;
    while((read = fread(&(*line)[line_offset], sizeof(char), read_size, f)) > 0){
        for(int i = 0; i < read; i++){
            if((*line)[line_len] == '\n') {
                if(line_len + 1 >= line_size) {
                    line_size = line_size * 2;
                    (*line) = realloc(*line, line_size);
                    if(*line == NULL) {
                        printf("Failed to reallocate to size %u", line_size);
                        exit(0);
                    }
                    *size = line_size;
                }
                line_len += 1;

                (*line)[line_len] = '\0';

                fseek(f, i-read + 1, SEEK_CUR);

                return line_len;
            }
            line_len++;
        }

        if(line_size == line_len) {
            line_size = line_size * 2;
            read_size = line_size / 2;
            (*line) = realloc(*line, line_size);
            if(*line == NULL) {
                printf("Failed to reallocate to size %u", line_size);
                exit(0);
            }

            *size = line_size;
            line_offset = line_len;
        }
    }

    (*line)[line_len + 1] = '\0';

    return line_len == 0? -1 : line_len;
}

int aoc_get_num(char *line, size_t len, size_t *start) {
    int idx = *start;
    int num = 0;
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

int **aoc_num_matrix(long row, long col) {
    int **matrix = malloc(row * sizeof(*matrix));
    for(long i = 0; i < row; i++) {
        matrix[i] = malloc(col * sizeof(**matrix));
        for(long j = 0; j < col; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

size_t aoc_line_to_nums(char *line, size_t read, int **arr, size_t *size, int sep_count) {
    int arr_size = *size;
    if(*arr != NULL && arr_size == 0) {
        printf("Array allocated but line len is set to 0.\n");
        exit(1);
    }

    if(*arr == NULL) {
        arr_size = arr_size > 0? arr_size: __DEFAULT__LINE__SIZE__;
        *size = arr_size;
        *arr = calloc(arr_size, sizeof(**arr));
        if(*arr == NULL) {
            printf("Failed to allocate to size %u", arr_size);
            exit(0);
        }
    }

    int i = 0;
    for(size_t idx = 0; idx < read - 1; i++){
        if(i >= arr_size) {
            arr_size = arr_size * 2;
            *arr = realloc(arr, arr_size * sizeof(**arr));
        }
        int Y = aoc_get_num(line, read, &idx);
        idx += sep_count;

        (*arr)[i] = Y;
    }
    return i;
}
