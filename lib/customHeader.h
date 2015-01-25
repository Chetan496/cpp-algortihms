#include<stdlib.h>
#if !defined(printf)
#include<stdio.h>
#endif
#define TRUE 1
#define FALSE 0
#define ARRAY_LENGTH(arr) ( sizeof arr / sizeof arr[0] )
#define LAST_INDEX(arr) ( (ARRAY_LENGTH(arr)) - 1 )
#define ERROR_CODE -999

void swap( int *num1, int *num2 ) {  
  int t = *num1;
  *num1 = *num2;
  *num2 = t;
}
/*prints the element in an array pointed to by ptr from firstIndex to lastIndex, inclusive
 */
void printarray(int *ptr, int firstIndex, int lastIndex){
   int i ;
   printf("\n-------------------------------------------------------------------\n");
   for(i = firstIndex; i <= lastIndex; i++ ){
      printf("%d ", *(ptr+i)) ;
   }
   printf("\n") ;
}


