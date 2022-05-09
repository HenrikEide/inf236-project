#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Merge
// a, b: arrays to merge
// l, r: left and right boundaries of the subarray
// end: end of the array
void merge(int *a, int *b, int l, int r, int end){
    int j, i = l, k = r;

    for (j = l; j < end; j++){
        if (i < r && (k >= end || a[i] <= a[k])){
            b[j] = a[i];
            i++;
        }
        else{
            b[j] = a[k];
            k++;
        }
    }
}

// Merge sort
// a: array to sort
// n: length of array
void mergeSort(int *a, int n) {
    int *b, *temp;
    float timeS, timeE;
    b = (int *) malloc(sizeof(int *)*n);
    timeS = omp_get_wtime();
    int w; // Width
    for (w = 1; w < n+1; w = 2 * w){
        for (int i = 0; i < n; i += 2 * w){
            int r = i + w;
            int end = i + 2 * w;
            if (r > n)
                r = n;
            if (end > n)
                end = n;
            merge(a, b, i, r, end);
        }
        temp = a;
        a = b;
        b = temp;
    }
    timeE = omp_get_wtime();
    printf("\nTime: %f\n", timeE - timeS);
}

int cmp(const void *a, const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}

// Main function
int main(){
    int n;
    printf("Enter the number of elements: \n");
    scanf("%d", &n);


    int *a = (int*)calloc(n, sizeof(int));
    int *test = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        a[i] = rand() % n;
        test[i] = a[i];
    }

    //Print the array, for testing
    // printf("Before sort: \n");
    // for(int i = 0; i < n; i++){
    //     printf("%d ", a[i]);
    // }

    mergeSort(a, n);

    // For testing
    qsort(test, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++){
        if (a[i] != test[i]){
            printf("\nError: Sorting failed at %d \n", i);
            break;
        }
    }
    

    // printf("\nAfter sort: \n");
    // for(int i = 0; i < n; i++){
    //     printf("%d ", a[i]);
    //     printf("%d \n", test[i]);
    // }
    // printf("\n");
}