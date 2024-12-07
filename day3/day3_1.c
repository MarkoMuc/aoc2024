#include "../includes/aoc.h"

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
    char keyword[] = {'m', 'u', 'l', '('};
    int counter = 0;
    long sum = 0;

    for(size_t idx = 0; idx < read; idx++){
        if(counter == 4) {
            int num1 = get_num(line, read, &idx, 0);
            if(num1 == -1) {
                counter = 0;
                continue;
            }
            idx++;
            int num2 = get_num(line, read, &idx, 1);
            if(num2 == -1) {
                counter = 0;
                continue;
            }
            sum += num1 * num2;
            counter = 0;
            continue;
        }

        if(counter >= 0 && line[idx] == keyword[counter]){
            counter++;
        }else{
            counter = 0;
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
