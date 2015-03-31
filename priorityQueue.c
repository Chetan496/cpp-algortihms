#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*A Priority queue is most efficiently implemented using a binary heap   */
/*The lower the value of the key the higher the priority. Key with the least key will be the root of the heap */
/*So, a priority queue here is a MIN-HEAP */
#define ARRAY_LENGTH(arr) (sizeof arr/sizeof arr[0])
#define PARENT(i) (i & 0x01) ? ( i >> 1) : ( (i-1) >> 1 )    /* C arrays start with 0. Hence the subtelity to get Parent */
#define LEFT(i) ( (i << 1) | 1 )
#define RIGHT(i) ( LEFT(i) + 1)
#define MID_HEAP_INDEX(heapSize) ( (heapSize >> 1 ) - 1 )

typedef struct Heap_t {
   int *arr;
   int arrlength;
   int heapSize;
} Heap_t, *Heap_p;

inline void swap( int *num1, int *num2) { int t = *num1 ;   *num1 = *num2;   *num2 = t;}

inline void print_error(char *msg) {
   printf("\n Error: %s \n", msg);
   abort();
}

inline void print_successMsg( char *msg ) {
   printf(" \n Success: %s \n" , msg) ;
}

/* This function maintains the min-heap property */
void heapify(Heap_p H, int i) {
   int l = LEFT(i)   ;
   int r = RIGHT(i) ;
   int least = (l <= H->heapSize-1 && ( H->arr)[l] < (H->arr)[i] ) ? l : i ;

   least = ( r<= H->heapSize-1 &&  (H->arr)[r] < (H->arr)[least]  ) ? r : least ;

   if( least != i )  {
      swap (  &(H->arr)[i] , &(H->arr)[least] ) ;
      if( least <=  MID_HEAP_INDEX(H->heapSize)  ){
        heapify(H, least) ;
      }
   }
}

/* This function inserts a new element with key into the heap.
 * It maintains the min-heap property while inserting*/
void heap_insert(Heap_p H, int key) {
   //expand the heap, add a new node to heap memory
   H->arr = (int *) realloc(H->arr, (H->heapSize + 1)*sizeof(int) ) ;
   if (H->arr == NULL) {
      print_error("Could not allocate memory for new element ");
   }
   H->heapSize = H->heapSize + 1 ;
   int i = H->heapSize - 1 ; //last index of heap is always one less than heapSize
   // i is pointing to last index in the heap. That location currently has garbage val      
   while( i>0 && (H->arr)[PARENT(i)] > key ) {

      (H->arr)[i] = (H->arr)[PARENT(i)]  ;
      i = PARENT(i);
   }

   (H->arr)[i] = key;
}

/*This function takes in a Heap ptr. as input and returns the element having the least value of its key k*/
/*It maintains the heap property by calling Heapify */
int heap_extract_min(Heap_p H){
   if(H == NULL) {
      print_error("The heap is not initialized ");
   }
   if(H->heapSize < 1) {
      print_error("Heap Underflow!");
   }
  
   int min = (H->arr)[0] ;
   (H->arr)[0] = (H->arr)[H->heapSize - 1] ;
   H->heapSize = H->heapSize - 1;
   heapify(H, 0);
   return min;
}

int heap_minimum(Heap_p H){
   if(H == NULL) {
      print_error("The heap is not initialized ");
   }
   if(H->heapSize < 1) {
      print_error("Heap Underflow!");
   }
   return (H->arr)[0] ;
}

/*Creates an empty heap and returns it */
Heap_p createHeap() {
   Heap_p H = (Heap_p) malloc(sizeof(Heap_t)) ;
   H->heapSize = 0;  
   H->arr = NULL;
   H->arrlength = 0;
   return H;
}

int main(){
 Heap_p q = createHeap();
 heap_insert(q, 2);
 heap_insert(q, 10);
 heap_insert(q, 1);
 heap_insert(q, 0);
 heap_insert(q, 4);

 printf("\n HIghest priority key is %d \n", heap_extract_min(q)) ;
 printf("\n HIghest priority key is %d \n", heap_extract_min(q)) ;
 heap_insert(q, -1);
 printf("\n HIghest priority key is %d \n", heap_extract_min(q)) ;
 printf("\n HIghest priority key is %d \n", heap_extract_min(q)) ;
 printf("\n HIghest priority key is %d \n", heap_extract_min(q)) ;
 return 0;
}
