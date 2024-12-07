#include "../includes/aoc.h"

#define ARR_LEN 3

char* xmas = "MAS";

int find_around(char** lines, int rows, int cols, int i, int j){
    int found = 0;

    //UP-LEFT->DOWN-RIGHT
    if(!((lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S' ) || (lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M'))) {
        return 0;
    }

    //UP-RIGHT->DOWN-LEFT
    if(!((lines[i-1][j+1] == 'M' && lines[i+1][j-1] == 'S') || (lines[i-1][j+1] == 'S' && lines[i+1][j-1] == 'M'))) {
        return 0;
    }

    return 1;
}

long find_xmas(char** lines, int rows, int cols){
    long count = 0;
    for(int i = 1; i < rows - 1; i++) {
        for(int j = 1; j < cols - 1; j++){
            if(lines[i][j] == 'A'){
                count += find_around(lines, rows, cols, i, j);
            }
        }
    }
    return count;
}

int main() {
    FILE *f = fopen("./case.in", "r");
    size_t size = 0;
    int read;
    int rows = 0;
    int cols = 0;
    char** lines = malloc(150 * sizeof(*lines));

    while((read = aoc_read_newline(f, &lines[rows], &size)) > 0) {
        if(cols == 0) {
            cols = read - 1;
        }
        lines[rows][read - 1] = '\0';
        rows++;
    }

    printf("%ld\n", find_xmas(lines, rows, cols));

    fclose(f);
    free(lines);
    exit(0);
}
