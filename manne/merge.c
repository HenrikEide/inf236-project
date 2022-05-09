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

  for(l=0;l<n_runs;l++) {
    mt1 = omp_get_wtime();

//*** Main loop ***
    int width;  // The length of the sequences being merged

    for (width = 1; width < dim; width = 2 * width)
    {
      int i;  // Points to the first of two sequences being merged

      /* array A is full of runs of length width */
      for (i = 0; i < dim; i = i + 2 * width)
        {
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
      /* copy array B to array A for next iteration */
      /*   a more efficient implementation would swap the roles of A and B */
      temp = A;
      A = B;
      B = temp;
      // CopyArray(A, B, n);
      /* now array A is full of runs of length 2*width */
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

  printf("\nSequential sorting of %d elements took %f seconds\n\n",dim,t_bs);

  int sorted = true;
  for(i=0;i<dim-1;i++) {
    if (A[i] > A[i+1])
      sorted = false;
  }
  if (!sorted)
    printf("The data is not sorted!!!\n");

}

int merge(int *A,int iLeft, int iRight, int iEnd,int *B) {
  int i0 = iLeft;
  int i1 = iRight;
  int j;
 
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
}
