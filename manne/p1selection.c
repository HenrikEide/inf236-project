#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define it_limit 512

#define max_threads 200

#define true 1
#define false 0

#define n_runs 1

int main(int argc, char *argv[]) {

  int *a,*B,*temp;
  int i,j,l,k;
  int num_proc;
  int dim;  // numbers to sort

  double mt1,mt2; // Timing variables
  float t_bs;
  int search;
  //int smallest,position;
  int tmp;
  int s[max_threads];
  int p[max_threads];
  int numberThreads;

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

//*** Code goes here ***
//
    for(i=0;i<dim-1;i++) {

#pragma omp parallel
      {
      int myid = omp_get_thread_num();

      int smallest = a[i];
      int position = i;

#pragma omp master
      numberThreads = omp_get_num_threads();
#pragma omp for private(j)
      for(j=i+1;j<dim;j++) {
       
        if (smallest > a[j])  {
            smallest = a[j];
            position = j;
        } // end if
      } // end for

      s[myid] = smallest;
      p[myid] = position;

      } // end parallel

// Now find the global smallest value
      int sm = s[0];
      int po = p[0];
      for(j=1;j<numberThreads;j++) {
        if (s[j]<sm) {
          sm = s[j];
          po = p[j];
        }
      }

// Swap smallest with the i'th value
      tmp = a[i];
      a[i] = sm;
      a[po] = tmp;
    } // end for
      

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

  printf("\nResult for selectionsort \n");
  printf("Sorting %d elements took %f seconds\n",dim,dim,t_bs);

  int sorted = true;
  for(i=0;i<dim-1;i++) {
    if (a[i] > a[i+1])
      sorted = false;
  }
  if (!sorted)
    printf("The data is not sorted!!!\n");


}
