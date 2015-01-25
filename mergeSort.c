/*
 * MERGE-SORT(A,p,r)
 * if p < r
 *   then q <- floor((p+r)/2)
 *        MERGE-SORT(A,p,q)
 *        MERGE-SORT(A,q+1,r)
 *        MERGE(A,p,q,r)
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printarray(int *ptr, int firstIndex, int lastIndex){
   int i ;
   printf("\n-------------------------------------------------------------------\n");
   for(i = firstIndex; i <= lastIndex; i++ ){
      printf("%d ", *(ptr+i)) ;
   }
   printf("\n") ;
}

void merge(int *ptr, int firstIndex, int mid, int lastIndex){
  /* *(ptr+firstIndex) to *(ptr+mid) is already sorted
   * *(ptr+mid+1) to *(ptr+lastIndex) is already sorted
   * just merge these two lists so that the resulting list is also sorted
   */
  int *l1, *l2 ;
  long unsigned int i=0,j=0,k=0, count1 = mid - firstIndex, count2 = lastIndex - mid + 1, count3 = count1 + count2 ;
  int *l3 = (int*)calloc(count3, sizeof *ptr)  ;
  l1 = ptr + firstIndex  ;
  l2 = ptr + mid ;
   
  while(i < count1 && j < count2 ){
    *(l3 + k++) =  *(l1 + i) <= *(l2 + j) ? *(l1 + i++) : *(l2 + j++) ;
  }

  if(i < count1){ memmove(l3 + k, l1 + i, (count1 - i) * sizeof *l1) ; } ;

  if(j < count2){ memmove(l3 + k, l2 + j, (count2 - j) * sizeof *l2) ; } ;
    //copy the items of l3 to ptr, to the appropriate block
  memmove(ptr+firstIndex, l3, count3 * sizeof *l3 ) ;  //efficient than for loop to copy
  free(l3) ; //l3 was  a temporary list, which needs to be freed 
}


void mergesort(int *ptr, int firstIndex, int lastIndex){
   int mid;
   if (firstIndex < lastIndex) {
           mid = (firstIndex + lastIndex)/2 ;
           mergesort(ptr, firstIndex, mid) ;
           mergesort(ptr, mid+1, lastIndex) ;
           merge(ptr, firstIndex, mid+1, lastIndex) ;
   }
    
}

int main(){
   int alist[15] = {2,190,10,-1,29,24,3,120, 31, 2, 0, 9,21,2,65} ;
   int *lptr = alist;
   printf("\nBefore sorting array was: \n") ;
   printarray(lptr, 0,  (int)(sizeof alist/sizeof *lptr)-1 );
   mergesort(lptr, 0, (int)(sizeof alist/sizeof *lptr)-1 ) ;
   printf("\nAfter calling mergesort sort procedure \n") ;
   printarray(lptr, 0,  (int)(sizeof alist/sizeof *lptr)-1 );
   return 0;
}


