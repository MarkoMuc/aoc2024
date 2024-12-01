#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "real.in"
#define ARR_SIZE 1000

int find_min(int* arr, int size){
    int min = -1;
    int idx = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] == -1) {
            continue;
        } else if(arr[i] < min || min == -1){
            idx = i;
            min = arr[i];
        }
    }
    arr[idx] = -1;

    return min;
}

int main(){
    FILE *f = fopen(FILE_NAME, "r");
    int read = 0;
    int count = 0;
    int arr_left[ARR_SIZE];
    int arr_right[ARR_SIZE];

    while(read != EOF){
        read = fscanf(f, "%d", &arr_left[count]);
        read = fscanf(f, "%d", &arr_right[count]);
        count++;
    }
    int out = 0;
    count = 0;

    while (count < ARR_SIZE) {
        int min_left = find_min(arr_left, ARR_SIZE);
        int min_right = find_min(arr_right, ARR_SIZE);
        out += abs(min_left - min_right);
        count++;
    }

    printf("%d\n", out);
    fclose(f);
    exit(0);
}

