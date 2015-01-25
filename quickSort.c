/*
 * QUICKSORT(A, p, r)
 * if p < r
 *  then q <- PARTITION(A,p,r)
 *     QUICKSORT(A,p,q)
 *     QUICKSORT(A,q+1,r)
 *
 *
 * PARTITION(A, p, r)
 * x <- A[p]
 * i <- p - 1
 * j <- r + 1
 *
 * while TRUE
 *   do repeat j <- j - 1
 *       until A[j] le x
 *      repeat i <- i + 1
 *       until A[i] ge x
 *
 *      if i < j
 *        then exchange A[i] <-> A[j]
 *        else return j
 *
 */

#include<stdio.h>
#include<string.h>
#include "lib/customHeader.h"

int partition(int *arrptr, int fIndex, int lIndex) {
    int pivotVal = arrptr[fIndex] ;
    int i = fIndex - 1, j = lIndex + 1 ;
    while(TRUE) {
        do {
            if (j == fIndex) {
                break;
            }
            j = j - 1 ;

        } while( *(arrptr + j) > pivotVal  ) ;

        do {
            if ( i == lIndex) {
                break;
            }
            i = i + 1;

        } while( *(arrptr + i) < pivotVal ) ;

        if ( i < j ) {
            swap( arrptr+i, arrptr+j  );
        } else {
            return j;
        }
    }
}

void quickSort( int *arrptr, int fIndex, int lIndex  ) {
   int mIndex ;   
   if ( fIndex < lIndex ) {
      mIndex = partition(arrptr, fIndex, lIndex) ;
      quickSort(arrptr, fIndex, mIndex) ;
      quickSort(arrptr, mIndex+1, lIndex) ;
   }
}

void quickSortWrapper( int *arrptr, int arrlength ){   quickSort(arrptr, 0, arrlength - 1) ;}

int main() {

    int alist[8] = {10, 7,4,0,1,-1,3,4} ;
    quickSortWrapper(alist, ARRAY_LENGTH(alist)) ;
    printf("\n After applying the quickSort algortihm on the array, the result is : \n") ;
    printarray(alist, 0, ARRAY_LENGTH(alist) - 1) ;
    return 0;
}
