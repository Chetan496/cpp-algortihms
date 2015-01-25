#include<stdio.h>
#include<stdlib.h>

/* let us write a function which merges two sorted arrays. The resulting array should be sorted */
/*eg: mergesortedarrays({1,3,4}, {2,5}) = {1,2,3,4,5} */

int* merge_sorted_arrays(int* lptr1, size_t count1, int* lptr2, size_t count2){

   long unsigned int i=0,j=0, k=0;
   /* allocate memory block to the new list. It will hold count1+count2 items*/
   int *newlistptr = (int *) calloc(count1+count2, sizeof *lptr1) ;

   while(i < count1 && j < count2){
         *(newlistptr + k++) =  *(lptr1+i) <= *(lptr2 + j) ? *(lptr1 + i++) : *(lptr2 + j++);
   }
   //either of list1 or list2 is finished. in either case, just append the remaining items to our new list
   while( i < count1){
      *(newlistptr + k++ )   = *(lptr1 + i++) ;
   }

   while( j < count2) {
      *(newlistptr + k++) = *(lptr2 + j++);
   }
   
   return newlistptr;
}


int main(){
   int list2[4] = {2,7,8,12};
   int list1[3] = {-1, 0, 10};
   int *lptr1 = list1, *lptr2 = list2;
   int *newlistptr = merge_sorted_arrays(lptr1, sizeof list1/sizeof *lptr1, lptr2, sizeof list2/sizeof *lptr2) ;
   
   printf("\n The new array after merging the two arrays is ...\n") ;

   for(long unsigned int i=0; i< ((sizeof list1/sizeof *lptr1)  + (sizeof list2/sizeof *lptr2) ); i++) {
   
      printf("%d ", *(newlistptr+i)) ;
   }
   return 0; 
}
