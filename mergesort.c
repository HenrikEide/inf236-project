#include <stdio.h>
#include <stdlib.h>

#define yes 1

// TODO: This needs to be fixed
// It is not working properly
// Stack smashing detected

// Merge
//   a: array to sort
//   b: temporary array
//   n: size of array
//   m: size of sub-arrays to merge
// void merge(int *a, int *b, int n, int m) {
//   int i, j, k;

//   for (i = j = k = 0; i < n && j < m; k++) {
//     if (a[i] <= b[j])
//       a[k] = a[i++];
//     else
//       a[k] = b[j++];
//   }
//   while (i < n)
//     a[k++] = a[i++];
//   while (j < m)
//     a[k++] = b[j++];

// }

// Merge c
void merge(int *a, int *b, int l, int r){
        int i, j, k;
    
    for(i = j = k = l; i < r; k++){
        if(a[i] <= a[j]){
            b[k] = a[i++];
        }
        else{
            b[k] = a[j++];
        }
    }
    while(i < r){ 
        b[k++] = a[i++];
    }
    while(j < r){
        b[k++] = a[j++];
    }
    for(i = l; i < r; i++){
        a[i] = b[i];
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
void mergeSort(int *a, int l, int r) {
  int mid;

  if (l < r) {
    mid = (l + r) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    merge(a, a + mid + 1, r - mid - 1, mid);
  }
}

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