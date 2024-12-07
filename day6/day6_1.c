#include "../includes/aoc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define _TEST_FILE_ "./case.in"
//#define _TEST_FILE_ "./case.test"

typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} dir;

#define MTRX_ROW 130
#define START_CHAR '^'

long play_game(char** lines, int rows, int len, int i, int j){
    long counter = 0;
    dir d = UP;

    while(true) {
        if(i == rows - 1 || i == 0 || j == len - 1 || j == 0){
            counter++;
            lines[i][j] = 'X';
            break;
        }

        if(lines[i][j] != 'X'){
            counter++;
            lines[i][j] = 'X';
        }else{
            lines[i][j] = 'X';
        }

        // UP
        if(d == UP) {
            if(lines[i-1][j] == '#'){
                j = j+1;
                d = RIGHT;
            }else{
                i = i-1;
            }
            continue;
        }

        // RIGHT
        if(d == RIGHT) {
            if(lines[i][j+1] == '#'){
                i = i+1;
                d = DOWN;
            }else{
                j = j+1;
            }
            continue;
        }

        // DOWN
        if(d == DOWN) {
            if(lines[i+1][j] == '#'){
                j = j-1;
                d = LEFT;
            }else{
                i = i+1;
            }
            continue;
        }

        // LEFT
        if(d == LEFT) {
            if(lines[i][j-1] == '#'){
                i = i-1;
                d = UP;
            }else{
                j = j-1;
            }
            continue;
        }
    }

    return counter;
}

int main() {
    FILE *f = fopen(_TEST_FILE_, "r");
    size_t size = 0;
    char* line = NULL;
    int read;

    int rows = 0;
    int len = 0;
    char** lines = malloc(MTRX_ROW * sizeof(*lines));

    int px = -1;
    int py = -1;
    while((read = aoc_read_newline(f, &lines[rows], &size)) > 0) {
        if(len == 0){
            len = read - 1;
        }

        lines[rows][len] = '\0';
        if(px == -1){
            for(int i = 0; i < len; i++){
                if(lines[rows][i] == START_CHAR){
                    px = rows;
                    py = i;
                }
            }
        }

        rows++;
    }
    printf("%ld\n", play_game(lines, rows, len, px, py));

    fclose(f);
    for(int i = 0; i < rows; i++) free(lines[i]);
    free(lines);
    exit(0);
}
