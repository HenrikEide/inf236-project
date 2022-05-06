#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define it_limit 512

#define true 1
#define false 0

#define n_runs 1

int main(int argc, char *argv[]) {

  int *A,*B,*temp;
  int i,l;

  int dim;  // numbers to sort

  double mt1,mt2; // Timing variables
  float t_bs;
  int merge();

  printf("Give length of array to sort \n");
  scanf("%d",&dim);
//  dim = 50000000;


  A = (int *) malloc(sizeof(int *)*dim);
  B = (int *) malloc(sizeof(int *)*dim);


  for(i=0;i<dim;i++) {    
    A[i] = random() % 1000;
  }

  if (dim <= 20) {
    printf("Unsorted data \n");
    for(i=0;i<dim;i++) {    
      printf("%d ",A[i]);
    }
    printf("\n");
  }

  // ****************************
  // Starting the main algorithm
  // ****************************


  t_bs = -1.0;
  int numproc;

  for(l=0;l<n_runs;l++) {
    mt1 = omp_get_wtime();


#pragma omp parallel 
    {
    int p = omp_get_num_threads();
    numproc = p;
    int myid = omp_get_thread_num();

    int width = dim/(2*p);

    int start = 2*myid*width;
    int midle = start + width;
    int stop = midle + width;
    int next = stop + width;

    if (myid == p-1) 
      stop = dim;

    mergeSort(&A[start],&B[start],midle-start);

    mergeSort(&A[midle],&B[midle],stop-midle);

    int ll,ii;

    for(ll=0;ll<2*p+1;ll++) {
    
      #pragma omp barrier
      if (ll%2 == 0) {
        
        merge(A,start,midle,stop,B);  // Even merge
      }
      else if (myid != p-1) {
        if (myid == 0)  // In odd stages, thread 0 must copy its first half to B
          memcpy(A,B,width*sizeof(int));

        merge(B,midle,stop,next,A);   // Odd merge
      }
      else // thread p-1 copies its last half to B
        memcpy(A+midle,B+midle,(stop-midle)*sizeof(int));
    }

    }
    mt2 = omp_get_wtime();
//*** Capture best run

    if ((t_bs < 0) || (mt2-mt1 < t_bs))
      t_bs = mt2-mt1;
  }


//*** Print out small instances

  if (dim <= 20) {
    printf("Sorted data \n");
    for(i=0;i<dim;i++) {
      printf("%d ",A[i]);
    }
    printf("\n");
  }

  printf("\nSorting of %d elements took %f seconds\n\n",dim,dim,t_bs);

  if (numproc%2 == 0)
    A = B;

  int sorted = true;
  for(i=0;i<dim-1;i++) {
    if (A[i] > A[i+1])
      sorted = false;
  }
  if (!sorted)
    printf("The data is not sorted!!!\n");

}


int mergeSort(int *A,int *B,int dim) {

  int width;  // The length of the sequences being merged
  int it=0;
  int k;

  int *pA = A;
  int *pB = B;


  for (width = 1; width < dim; width = 2 * width) {
    int i;  // Points to the first of two sequences being merged

    /* array A is full of runs of length width */
    for (i = 0; i < dim; i = i + 2 * width) {
      /* merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[] */
      /*  or copy A[i:n-1] to B[] ( if(i+width >= n) ) */
      int iRight = i+width;
      int iEnd = i+2*width;

      if (dim < iRight)
        iRight = dim;
      if (dim < iEnd)
        iEnd = dim;

      merge(A,i,iRight,iEnd,B);
    }
 
    /* now work array B is full of runs of length 2*width */

    
    int *temp = A;
    A = B;
    B = temp;
    it++;
    /* now array A is full of runs of length 2*width */
  }

  if (it%2 == 1)
    memcpy(pA,pB,dim*sizeof(int));

}

int merge(int *A,int iLeft, int iRight, int iEnd,int *B) {
  int i0 = iLeft;
  int i1 = iRight;
  int i,j;
/* 
  printf("Merging (%d,%d): \n",iLeft,iEnd);
  for(i=iLeft;i<iEnd;i++) {
    printf("%d ",A[i]);
  }
  printf("\n");
*/
  /* while there are elements in the left or right lists */
  for (j = iLeft; j < iEnd; j++)
    {
      /* if left list head exists and is <= existing right list head */
      if (i0 < iRight && (i1 >= iEnd || A[i0] <= A[i1]))
        {
          B[j] = A[i0];
          i0 = i0 + 1;
        }
      else
        {
          B[j] = A[i1];
          i1 = i1 + 1;
        }
    }
/*
  printf("Into (%d,%d): \n",iLeft,iEnd);
  for(i=iLeft;i<iEnd;i++) {
    printf("%d ",B[i]);
  }
  printf("\n");
*/
}
