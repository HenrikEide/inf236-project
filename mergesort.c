#include <stdio.h>
#include <stdlib.h>


// Merge
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
void mergeSort(int *a, int n) {
    int *b, *temp;
    b = (int *) malloc(sizeof(int *)*n);

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
}


// Main function, for testing
int main(){
    int a[] = {4, 2, 5, 1, 3, 8, 7, 6};
    int n = sizeof(a)/sizeof(a[0]);

    printf("Before sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    
    mergeSort(a, n);

    printf("\nAfter sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}