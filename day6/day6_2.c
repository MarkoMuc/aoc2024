#include "../includes/aoc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define _TEST_FILE_ "./case.in"
//#define _TEST_FILE_ "./case.test"

typedef enum {
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4
} dir;

#define MTRX_ROW 130
#define START_CHAR '^'

typedef struct {
    int cx;
    int cy;
    int cd;
} step;

typedef struct {
    step *steps;
    long count;
    long size;
} step_arr;

void init_step(step_arr *arr){
    arr->steps = malloc(arr->size * sizeof(step));
}

void add_step(step_arr *arr, step stp){
    if(arr->count >= arr->size) {
        arr->size = arr->size * 2;
        arr->steps = realloc(arr->steps, arr->size * sizeof(step));
    }
    arr->steps[arr->count] = stp;
    arr->count = arr->count + 1;
}

int contains_step(step_arr arr, step stp){
    for(int i=0; i < arr.count; i++){
        step st = arr.steps[i];
        if(st.cd == stp.cd){
            return 1;
        }
    }
    return 0;
}

long play_game(char** lines, int rows, int len, int px, int py, int** mtrx, step_arr **walk_mtrx){
    dir d = UP;
    int i = px;
    int j = py;
    dir sd = d;
    long res = -1;

    while(true) {
        if(i == rows - 1 || i == 0 || j == len - 1 || j == 0){
            res = 0;
            if(mtrx != NULL){
                mtrx[i][j] = 1;
            }
            break;
        }

        if(mtrx != NULL){
            if(mtrx[i][j] != 1){
                mtrx[i][j] = 1;
            }
        }

        step stp = {.cd = d, .cy = j, .cx = i};
        if(contains_step(walk_mtrx[i][j], stp)){
            res = 1;
            break;
        }else{
            add_step(&walk_mtrx[i][j], stp);
        }

        // UP
        if(d == UP) {
            if(lines[i-1][j] == '#' || lines[i-1][j] == 'O'){
                d = RIGHT;
                //j = j+1;
            }else{
                i = i-1;
            }
            continue;
        }

        // RIGHT
        if(d == RIGHT) {
            if(lines[i][j+1] == '#' || lines[i][j+1] == 'O'){
                d = DOWN;
                //i = i+1;
            }else{
                j = j+1;
            }
            continue;
        }

        // DOWN
        if(d == DOWN) {
            if(lines[i+1][j] == '#' || lines[i+1][j] == 'O'){
                d = LEFT;
                //j = j-1;
            }else{
                i = i+1;
            }
            continue;
        }

        // LEFT
        if(d == LEFT) {
            if(lines[i][j-1] == '#' || lines[i][j-1] == 'O'){
                d = UP;
                //i = i-1;
            }else{
                j = j-1;
            }
            continue;
        }
    }

    for(int i=0; i< rows; i++){
        for(int j=0; j< len; j++){
            walk_mtrx[i][j].count = 0;
        }
    }

    return res;
}

long play_game_block(char** lines, int rows, int len, int px, int py, int **mtrx, step_arr **walk_mtrx){
    long counter = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < len; j++) {
            if((i == px && j == py)){
                continue;
            }

            if(mtrx[i][j] == 1){
                char hold = lines[i][j];
                lines[i][j] = 'O';
                counter += play_game(lines, rows, len, px, py, NULL, walk_mtrx);
                lines[i][j] = hold;
            }
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
    while((read = read_newline(f, &lines[rows], &size)) > 0) {
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

    int **mtrx_steps = num_matrix(rows, len);
    step_arr **walk_mtrx = malloc(rows * sizeof(*walk_mtrx));

    for(long i = 0; i < rows; i++) {
        walk_mtrx[i] = malloc(len * sizeof(**walk_mtrx));
        for(long j = 0; j < len; j++){
            walk_mtrx[i][j].size = 256;
            walk_mtrx[i][j].count = 0;
            init_step(&walk_mtrx[i][j]);
        }
    }

    play_game(lines, rows, len, px, py, mtrx_steps, walk_mtrx);
    printf("%ld\n", play_game_block(lines, rows, len, px, py, mtrx_steps, walk_mtrx));

    fclose(f);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < len; j++) {
            free(walk_mtrx[i][j].steps);
        }
        free(walk_mtrx[i]);
    }
    free(walk_mtrx);

    for(int i = 0; i < rows; i++) free(lines[i]);
    free(lines);

    for(int i = 0; i < rows; i++) free(mtrx_steps[i]);
    free(mtrx_steps);
    exit(0);
}
