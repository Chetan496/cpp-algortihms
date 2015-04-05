#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "minunit/minunit.h" 
#define NOTFOUND -1
/*
 *Given two Strings,like  X = ABCBDAB and Y = BCDDA
 this program find the lengths of the longest common sequence of the two strings
eg: here longest common sequence is BCDA - with length 4
 */
/*
 *This program uses the MinUnit library for unit testing the lcs function.
 Also refer to the makefile. An extra -lrt flag has been added
 */
typedef size_t Length ;
typedef size_t Integer ;  //it will be unsigned positive integr



int lcs_lookup ( char *strX, Length xlen, char *strY, Length ylen,  int **c ) {

   if (xlen == 0 || ylen == 0) {
      return 0 ;
   }

   if ( c[xlen][ylen] != NOTFOUND ) {
      return c[xlen][ylen] ;  //the solution to this problem was already found
   }
   
   if ( strX[xlen-1] == strY[ylen-1] ) {  //last array index = length of array - 1 
   
      c[xlen][ylen] = 1 + lcs_lookup(strX, xlen - 1, strY, ylen - 1, c) ;
      return c[xlen][ylen] ;
   }

   Integer l1, l2 ;
   l1 = lcs_lookup(strX, xlen, strY, ylen - 1, c ) ;
   l2 = lcs_lookup(strX, xlen - 1, strY, ylen , c) ;
   c[xlen][ylen] = (l1>=l2)?l1:l2 ;

   return c[xlen][ylen] ;

}

/*This function finds th longest common subsequence of two strings X and Y */
int lcs(  char *strX,  char *strY    ){
   
   if (strX == NULL || strY == NULL) {
      return 0 ;
   }
   Length xlen = strlen(strX) ;
   Length ylen = strlen(strY);
   int **c = (int **)  calloc(xlen + 1 , sizeof(int *)) ;
   Integer i, j ;
   int lcs_len;

   for (i = 0; i < xlen + 1; i++) {
   
      c[i] = (int *)calloc(ylen + 1, sizeof(int)  ) ;
   }
   
   // c is now an array of size (x_len + 1) * (y_len + 1)
   // c[i][j] represents the length of lcs of substrings Xi and Yj
   // c[i][0] for all i from i=1 to i=x_len and c[0][j] = 0 for all j from j=1 to j=y_len
   // and c[0][0] = 0
   c[0][0] = 0 ;

   for (i = 1; i <= xlen; i++) {
      c[i][0] = 0;
   }
   for(j=1; j <= ylen; j++ ) {
      c[0][j] = 0;
   }
   
   for ( i = 1; i <= xlen; i++) {
   
      for ( j= 1; j <= ylen; j++) {
         
         c[i][j] = NOTFOUND ;  //to indicate that we have to yet calculate them
      }
   }
   
   // what we finally want to find out is c[xlen][ylen]
   lcs_len = lcs_lookup(strX, xlen, strY, ylen, c) ;
   for (i=0; i < xlen+1; i++) {
      free(c[i]) ;
   }
   free(c) ;
   return lcs_len ;

}

MU_TEST(test_lcs_normal){
   char *X = "BACBADBA" ;
   char *Y = "CDABC" ;
   int l = lcs(X,  Y ) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 3) ;
}
MU_TEST(test_lcs_xempty){
   char *X = "" ;
   char *Y = "CDABC" ;
   int l = lcs(X,  Y) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 0) ;
}
MU_TEST(test_lcs_yempty){
   char *X = "BACBADBA" ;
   char *Y = "" ;
   int l = lcs(X,  Y) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 0) ;
}
MU_TEST(test_lcs_bothempty){
   char *X = "" ;
   char *Y = "" ;
   int l = lcs(X,  Y) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 0) ;
}
MU_TEST(test_lcs_longX){
   char *X = "BACBADBAABCBCABBAACABCADDABCBBDDBABADC" ;
   char *Y = "CDABC" ;
   int l = lcs(X, Y) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 5) ;
}
MU_TEST(test_lcs_longY){
   char *X = "BACBADBA" ;
   char *Y = "CDABCBCDABCDABCDAADCNCDABCADCABCBDFDACNCAD" ;
   int l = lcs(X,  Y) ;
   printf("\n l was %d \n ", l);
   mu_check(l == 8) ;
}

MU_TEST(test_lcs_bothlong){
   char *X = "BACBADBAABCBCABBAACABCADDABCBBDDBABADC" ;
   char *Y = "CDABCBCDABCDABCDAADCNCDABCADCABCBDFDACNCAD" ;
   int l = lcs(X,  Y) ;
   printf("\n l was %d  in bothlong\n ", l);
   mu_check(l == 27) ;
}


MU_TEST_SUITE(test_suite) {
   MU_RUN_TEST(test_lcs_normal) ;
   MU_RUN_TEST(test_lcs_xempty) ;
   MU_RUN_TEST(test_lcs_yempty) ;
   MU_RUN_TEST(test_lcs_bothempty) ;
   MU_RUN_TEST(test_lcs_longX) ;
   MU_RUN_TEST(test_lcs_longY) ;
   MU_RUN_TEST(test_lcs_bothlong) ;

}
int main(){
   MU_RUN_SUITE(test_suite) ;
   MU_REPORT() ;
   return 0 ;
}
