#include "../includes/aoc.h"

int enabled = 1;

int get_num(char *line, size_t len, size_t *start, int second) {
    int idx = *start;
    int num = 0;
    if(*start >= len - 1) {
        return -1;
    }

    int counter = 0;
    for(; idx < len; idx++) {
        if(counter > 3) {
            num = -1;
            break;
        }

        if(line[idx] >= '0' && line[idx] <= '9') {
            num = num * 10 + (line[idx] - '0');
            counter++;
        }else {
            if(counter > 0 && counter < 4
                && ((line[idx] == ',' && !second) || (line[idx] == ')' && second))) {
            }else{
                num = -1;
            }
            break;
        }
    }

    *start = idx;
    return num;
}

long parse_line(char *line, size_t read){
    char* kw[] = {"mul(", "do()", "don't()"};
    int c_col = 0;
    int c_row = -1;
    long sum = 0;

    for(size_t idx = 0; idx < read; idx++){
        if(c_row == 0){
            if(c_col == 4) {
                int num1 = get_num(line, read, &idx, 0);
                if(num1 == -1) {
                    c_col = 0;
                    c_row = -1;

                    idx--;
                    continue;
                }
                idx++;

                int num2 = get_num(line, read, &idx, 1);
                if(num2 == -1) {
                    c_col = 0;
                    c_row = -1;

                    idx--;
                    continue;
                }

                if(enabled){
                    sum += num1 * num2;
                }

                c_col = 0;
                c_row = -1;

                continue;
            }
            if(line[idx] == kw[c_row][c_col]){
                c_col++;
                continue;
            }else{
                c_col = 0;
                c_row = -1;
            }

        } else if(c_row == 1 || c_row == 2){
            if(c_col == 2 && line[idx] == 'n') {
                c_row = 2;
                c_col++;
                continue;
            }

            if(c_row == 1 && c_col == 4){
                enabled = 1;
                c_col = 0;
                c_row = -1;
            } else if (c_row == 2 && c_col == 7){
                enabled = 0;
                c_col = 0;
                c_row = -1;
            }

            if(c_row >= 1 && line[idx] == kw[c_row][c_col]){
                c_col++;
                continue;
            }else{
                c_col = 0;
                c_row = -1;
            }
        }

        if(c_row == -1 && line[idx] == 'm'){
            c_row = 0;
            c_col++;
        }else if(c_row == -1 && line[idx] == 'd'){
            c_row = 1;
            c_col++;
        }else{
            c_row = -1;
            c_col = 0;
        }

    }
    return sum;
}

int main() {
    FILE *f = fopen("./case.in", "r");
    char* line = NULL;
    size_t size = 0;
    int read;
    long value = 0;

    while((read = aoc_read_newline(f, &line, &size)) > 0) {
        value += parse_line(line, read);
    }

    printf("%ld\n", value);

    fclose(f);
    free(line);
    exit(0);
}
