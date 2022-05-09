#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


// Parallel merge
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


// Parallel merge sort
void mergeSort(int *a, int n) {
    float timeS, timeE;

#pragma omp parallel
#pragma omp master 
    { int nthreads = omp_get_num_threads();}
    int *b, *temp;
    b = (int *) malloc(sizeof(int *)*n);
#pragma omp master
    { timeS = omp_get_wtime();}
    int w; // Width
    for (w = 1; w < n+1; w = 2 * w){
#pragma omp barrier
#pragma omp for
        for (int i = 0; i < n; i += 2 * w){
            int r = i + w;
            int end = i + 2 * w;
            if (r > n)
                r = n;
            if (end > n)
                end = n;
            merge(a, b, i, r, end);
        }
#pragma omp barrier
#pragma omp master 
    {
        temp = a;
        a = b;
        b = temp;
    }
    }
#pragma omp master
    { timeE = omp_get_wtime();
    printf("\nTime: %f\n", timeE - timeS);
    }
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
    printf("\n");
}