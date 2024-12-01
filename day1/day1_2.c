#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "real.in"
#define ARR_SIZE 1000

int find_same(int find, int* arr, int size){
    int same = 0;
    for(int i = 0; i < size; i++) {
        if(find == arr[i]){
            same++;
        }
    }
    return same * find;
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
        out += find_same(arr_left[count], arr_right, ARR_SIZE);
        count++;
    }

    printf("%d\n", out);
    fclose(f);
    exit(0);
}

