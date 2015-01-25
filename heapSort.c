#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARRAY_LENGTH(arr) (sizeof arr/sizeof arr[0])
#define PARENT(i) (i & 0x01) ? ( i >> 1) : ( (i-1) >> 1 )    /* C arrays start with 0. Hence the subtelity to get Parent */
#define LEFT(i) ( (i << 1) | 1 )
#define RIGHT(i) ( LEFT(i) + 1)
#define MID_HEAP_INDEX(heapSize) ( (heapSize >>1 ) - 1 )

struct heapObj {
   int *arrptr;
   size_t arrlength;
   size_t heapSize;
};

typedef struct heapObj HeapObj;
typedef HeapObj *HeapPtr;  

void swap( int *num1, int *num2) { int t = *num1 ;   *num1 = *num2;   *num2 = t;}

void heapify(HeapPtr aHeap, size_t i) {
   size_t l = LEFT(i)   ;
   size_t r = RIGHT(i) ;
   size_t largest = (l <= aHeap->heapSize-1 && ( aHeap->arrptr)[l] > (aHeap->arrptr)[i] ) ? l : i ;

   largest = ( r<= aHeap->heapSize-1 &&  (aHeap->arrptr)[r] > (aHeap->arrptr)[largest]  ) ? r : largest ;

   if( largest != i )  {
      swap (  &(aHeap->arrptr)[i] , &(aHeap->arrptr)[largest] ) ;
      if( largest <=  MID_HEAP_INDEX(aHeap->heapSize)  ){
        heapify(aHeap, largest) ;
      }
   }
}
/*
 *This procedure takes in 1. pointer to an array and 2. Its length.
 * It then constructs a heap object out of it. Then returns it.
 */
HeapPtr buildHeap( int *arrptr, size_t arr_length){
   HeapPtr aHeap  =   (HeapPtr) malloc( sizeof(HeapObj) );  //the memory will be allocated from the heap
   int i, startIndex ;
   aHeap->arrlength = arr_length;
   aHeap->heapSize = arr_length ;
   aHeap->arrptr = arrptr;
   startIndex = MID_HEAP_INDEX(aHeap->heapSize);
   for( i = startIndex ; i>=0; i-- ) { heapify(aHeap, i) ; }
   return aHeap ;
}

void heapSort(int *arrptr, size_t arr_length) {
  HeapPtr aHeap = buildHeap(arrptr, arr_length) ;
  int i, lastIndex = aHeap->arrlength - 1 ;
  for(i = lastIndex ; i >= 1; i=i-1 ) {
     swap( (aHeap->arrptr + 0), (aHeap->arrptr + i)  ) ;
     aHeap->heapSize = aHeap->heapSize - 1 ;
     heapify(aHeap, 0 ) ; 
  }
  free(aHeap) ;  //we are done sorting. release memory allocated to the Heap
}

int main(){
  int alist[20] = {200,190,10,-1,29,24,3,120, 31, 2, 0, 9,21,2,65,4,7,1,-9,2} ;
  int *arrptr = alist; size_t i;
  heapSort(arrptr,   ARRAY_LENGTH(alist) ) ;
  printf("\n After applying the Heap Sort sorting algorithm the array is: \n");
  for(i=0; i < ARRAY_LENGTH(alist); i++) {
    printf("%d ", alist[i]) ;
  }
  printf("\n") ;
  return 0;
}
