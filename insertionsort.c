/* INSERTION-SORT(A)
 * for j<-2 to length[A]
 *   do key <- A[j]
 *  // Insert A[j] into the sorted sequence A[1...j-1]
 *  i <- j-1
 *  while i > 0 and A[i] > key
 *    do A[i+1] = A[i]
 *    i = i -1
 *
 * A[i+1] = key
 *
 */

#include<stdio.h>
#include<stdlib.h>

int*  insertion_sort(int *lptr, size_t n){
   int i, j;
   int count = (int) n ;  /*count is length of array pointed to by lptr */
   int key;

   for(j=1 ; j < count; j++){
     key = *(lptr+j) ;
     i = j - 1;
     while( i >= 0 && *(lptr+i) > key ) {
        *(lptr+i+1) = *(lptr+i);
        i = i - 1 ;
     }

     *(lptr+i+1) = key;
   }
   return lptr;
}

void print_array(int *lptr, size_t n){
   int i = 0;
   int count = (int) n;
   printf("\n----------------------------------------------------------------------------------------\n") ;
   for(i=0; i < count; i++){
     printf("%d ", *(lptr+i)) ;
   }
   printf("\n----------------------------------------------------------------------------------------\n") ;
}

int main(){
   int alist[10] = {1,0,10,2,2,5,9,3,4,6};
   int *lptr = alist;
   insertion_sort(lptr, sizeof alist/sizeof *lptr);
   printf("Sorted the array! \n") ;
   print_array(lptr, sizeof alist/sizeof *lptr) ;
   return 0;
}
