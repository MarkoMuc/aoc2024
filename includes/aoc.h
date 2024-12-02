#include <stdio.h>
#include <stdlib.h>

#define __DEFAULT__LINE__SIZE__ 256

#ifdef DEBUG
int read_line(FILE *f, char** line, size_t *size);
#endif

#ifndef DEBUG
int read_newline(FILE *f, char** line, size_t *size) {
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
        *line = malloc(line_size * sizeof(*line));
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
#endif

