#include "../includes/aoc.h"

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
    while((read = read_newline(f, &line, &size)) > 0) {
        int correct = 1;
        size_t start = 0;
        int num1 = get_num(line, read, &start);
        int asc = -1;

        while(1) {
            int num2 = get_num(line, read, &start);

            if(num2 == -1){
                break;
            }

            int diff = num2 - num1;

            if(abs(diff) < 1 || abs(diff) > 3) {
                correct = 0;
                break;
            }

            if(asc == -1) {
                asc = diff < 0 ? 0: 1;
            }

            if((diff > 0 && !asc) || (diff < 0 && asc)){
                correct = 0;
                break;
            }

            num1 = num2;
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
