#include "../includes/aoc.h"

char* xmas = "XMAS";
enum directions {
    S,
    U,
    D,
    L,
    R,
    UL,
    UR,
    DL,
    DR
};

int find_around(char** lines, int rows, int cols, int i, int j, int idx, enum directions dir){
    int found = 0;
    idx++;

    if(lines[i][j] != xmas[idx]){
        return 0;
    }else if(idx == 3){
        return 1;
    }

    //UP
    if((dir == S || dir == U) && i-1 >= 0){
        found += find_around(lines, rows, cols, i-1, j, idx, U);
    }
    
    //DOWN
    if((dir == S || dir == D) && i+1 < rows){
        found += find_around(lines, rows, cols, i+1, j, idx, D);
    }

    //LEFT
    if((dir == S || dir == L) && j-1 >= 0){
        found += find_around(lines, rows, cols, i, j-1, idx, L);
    }

    //RIGHT
    if((dir == S || dir == R) && j+1 < cols){
        found += find_around(lines, rows, cols, i, j+1, idx, R);
    }

    //UP-LEFT
    if((dir == S || dir == UL) && i-1 >= 0 && j-1 >= 0){
        found += find_around(lines, rows, cols, i-1, j-1, idx, UL);
    }

    //UP-RIGHT
    if((dir == S || dir == UR) && i-1 >= 0 && j+1 < cols){
        found += find_around(lines, rows, cols, i-1, j+1, idx, UR);
    }

    //DOWN-LEFT
    if((dir == S || dir == DL) && i+1 < rows && j-1 >= 0){
        found += find_around(lines, rows, cols, i+1, j-1, idx, DL);
    }

    //UP-RIGHT
    if((dir == S || dir == DR) && i+1 < rows && j+1 < cols){
        found += find_around(lines, rows, cols, i+1, j+1, idx, DR);
    }

    return found;
}

long find_xmas(char** lines, int rows, int cols){
    long count = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++){
            if(lines[i][j] == 'X'){
                count += find_around(lines, rows, cols, i, j, -1, S);
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

    while((read = read_newline(f, &lines[rows], &size)) > 0) {
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
