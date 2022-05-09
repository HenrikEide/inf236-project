#include <stdio.h>
#include <stdlib.h>

#define yes 1



// Merge c
void merge(int *a, int *b, int l, int r, int end){
    int j, i = l, k = r;

    for (j = l; j < end; j++){
        if (i < r && (k >= end || a[i] <= a[k])){
            b[j] = a[i++];
        }
        else{
            b[j] = a[k++];
        }
    }
}

// Merge sort
// void mergeSort(int *a, int n) {
//   int *b;
//   int mid;

//   if (n < 2)
//     return;
//   mid = n / 2;
//   b = a + mid;
//   mergeSort(a, mid);
//   mergeSort(a + mid, n - mid);
//   merge(a, b, n, mid);
// }

// Merge sort c
void mergeSort(int *a, int n) {
    int *b, *temp;
    b = (int *) malloc(sizeof(int *)*n);

    int w; // Width
    for (w = 1; w < n; w = 2 * w){
        int i;
        for (i = 0; i < n; i += 2 * w){
            int r = i + 2;
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
//   int mid;

//   if (l < r) {
//     mid = (l + r) / 2;
//     mergeSort(a, l, mid);
//     mergeSort(a, mid + 1, r);
//     merge(a, a + mid + 1, r - mid - 1, mid);
//   }


// Main function, for testing
int main(){
    int a[] = {4, 2, 5, 1, 3, 8, 7, 6};
    int n = sizeof(a)/sizeof(a[0]);

    printf("Before sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    
    mergeSort(a, 0, n);

    printf("\nAfter sort: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    return 0;
}