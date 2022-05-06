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

  int *a,*B,*temp;
  int i,l,k;
  int num_proc;
  int dim;  // numbers to sort

  double mt1,mt2; // Timing variables
  float t_bs;
  int search;
  int tmp;

  printf("Give length of array to sort \n");
  scanf("%d",&dim);
//  dim = 50000000;


  a = (int *) malloc(sizeof(int *)*dim);

  for(i=0;i<dim;i++) {    
    a[i] = random() % 1000;
  }

  if (dim <= 20) {
    printf("Unsorted data \n");
    for(i=0;i<dim;i++) {    
      printf("%d ",a[i]);
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
#pragma omp parallel
    {
      int j;
      int start=0;
      for(j=0;j<dim;j++)	{
        #pragma omp for private(tmp,i)
        for (i=start; i<dim-1; i+=2) { // Jump in steps by 2!
          if (a[i]>a[i+1]) {
            tmp=a[i];a[i]=a[i+1];a[i+1]=tmp;
          }
        }
        start = 1-start;  // Flip between 0 and 1: One thread only!
      } // end while
    } // end parallel

    mt2 = omp_get_wtime();

//*** Capture best run

    if ((t_bs < 0) || (mt2-mt1 < t_bs))
      t_bs = mt2-mt1;
  }


//*** Print out small instances

  if (dim <= 20) {
    printf("Sorted data \n");
    for(i=0;i<dim;i++) {
      printf("%d ",a[i]);
    }
    printf("\n");
  }

  printf("\nResult for parallel odd-even sort \n");
  printf("Sorting %d elements took %f seconds\n",dim,dim,t_bs);

  int sorted = true;
  for(i=0;i<dim-1;i++) {
    if (a[i] > a[i+1])
      sorted = false;
  }
  if (!sorted)
    printf("The data is not sorted!!!\n");


}
