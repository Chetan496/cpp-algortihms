#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef struct Pos_t {
   int x;
   int y;
} Pos_t, *Pos_p ;

typedef struct Rat_t {
   Pos_p pos ;
} Rat_t, *Rat_p ;

typedef enum Dir {UP,RIGHT, LOWER, LEFT} Dir;

int abs_value( int t1, int t2) ;

int change_in_temp( int **T, int x1, int y1, int x2, int y2 )  ;

Dir bestDirToMove(int **T, int maxX, int maxY, Pos_p pos ) ;

void moveRat(Rat_p rat, Dir dir) ;

char** RatsPositions(char* input1[] , char* inut2[], int input3 ) ;

Rat_p initializeRat( int x, int y )  ;

Pos_p initializePos( int x, int y ) ;

int** initializeTemp(char *strArray[]) ;

char* getPosAsStr(Pos_p p) ;

void reverse(char str[], int length) ;

char* itoa(int num, char *buffer, int base) ;

int myAtoi(char *str) ;

int* getIntsFromTempString( char *str) ;

char** RatsPositions(char* input1[], char* input2[], int input3)
{

   

}

int abs_value( int t1, int t2)
{
   int diff = t1 - t2 ;
   return ( ( diff < 0 ) ? (-1 * diff) : diff  ) ;
}


int change_in_temp( int **T, int x1, int y1, int x2, int y2) 
{
   return abs_value( T[x1][y1], T[x2][y2] ) ;

}


Dir bestDirToMove(  int **T, int maxX, int maxY,  Pos_p pos ) 
{

   int x = pos->x;
   int y = pos->y ;
   int del_left, del_right, del_up, del_lower ;
   Dir d;
   
   if (  (x-1) == 0   ) {
      del_left = 0 ;
   }else{
      del_left = change_in_temp( T, x, y, x-1, y ) ;
   }
   
   if ( (x+1) == (maxX + 1) ) {
      del_right = 0 ;
   }else{
      del_right = change_in_temp(T, x, y, x+1, y) ;
   }

   if ( (y-1) == 0 ) {
      del_up = 0 ;
   }else{
      del_up = change_in_temp(T, x, y, x , y-1) ;
   }

   if ( (y+1) == (maxY + 1) ) {
      del_lower = 0;
   }else{
      del_lower = change_in_temp(T, x, y, x, y+1) ;
   }

   int *t = (int *)calloc(4, sizeof(int)) ;
   t[0] = del_left ;
   t[1] = del_lower;
   t[2] = del_right ;
   t[3] = del_up ;
   
   int i;
   int maxIndex = 0;
   int max = t[0] ;

   for( i = 1; i < 4; i++ ) {
      if (t[i] > max) {
         max = t[i];
         maxIndex = i ;
      }
   }
   
   if(maxIndex == 0) {
      d =  LEFT;
   }
   if(maxIndex == 1){
      d  = LOWER;
   }
   if(maxIndex == 2) {
      d =  RIGHT;
   }
   if (maxIndex == 3) {
      d =  UP ;
   }

   return d;
}


void moveRat(Rat_p rat, Dir dir) {
   if (dir == UP) {
      rat->pos->y = rat->pos->y - 1;
   }
   else if (dir == RIGHT) {
      rat->pos->x = rat->pos->x + 1 ;
   }
   else if ( dir == LOWER) {
      rat->pos->y = rat->pos->y + 1;
   }
   else { 
      //move Left
      rat->pos->x = rat->pos->x - 1;
   }
}

Pos_p initializePos(int x, int y) {
   Pos_p p = (Pos_p) calloc(1, sizeof(Pos_t)) ;
   p->x = x;
   p->y = y;
   return p ;
}

Rat_p initializeRat(int x, int y) {
   Rat_p rat = (Rat_p) calloc(1, sizeof(Rat_t)) ;
   rat->pos = initializePos(x, y) ;
   return rat;
}

int **initializeTemp(char *strArray[]) {

   //returns a 2d Array, each of which contains temperature
   //the 0th row and col will not be used. instead we will add extra row and col
   int **T = NULL ;
   int rowTotal = 0,  i;
   while( strArray[rowTotal] != NULL ) {
      rowTotal = rowTotal + 1;

   }

   T = (int **) calloc( rowTotal + 1, sizeof(int *) ) ;

   for( i=1 ; i < rowTotal + 1 ; i++) {
   
      T[i] = getIntsFromTempString( strArray[i-1] ) ;
   }

   return T ;
}

int* getIntsFromTempString( char *str) 
{
   //str is a string separated by hashes
   //we need to create an Int array from it and return it 
   int *arr = NULL ;
   //array size will be = num. of hashes in the string + 1
   int numOfTokens = 0, i = 0;
   char *token ;
   while(str[i] != '\0') {
      if (str[i] == '#') {
         numOfTokens = numOfTokens  + 1 ;
      }
   }
   //there are (numTokens + 1) numbers in the string str
   //we need one extra col.
   arr = (int *)calloc( (numOfTokens + 2) , sizeof(int)) ;
   
   token = strtok(str, "#") ;
   for (i=1; i <= (numOfTokens + 1) ; i++) {
      arr[i] = myAtoi(token) ;
      token = strtok(NULL, "#") ;

      if (token == NULL){
         break ;
      }
   }

   return arr ;

}


char *getPosAsStr(Pos_p p) {
  int x = p->x ;
  int y = p->y;

  char *str_x = (char *)calloc(100, sizeof(char)) ;
  str_x = itoa(x, str_x, 10) ;
  char *str_y = (char *)calloc(100, sizeof(char))  ;
  str_y = itoa(y, str_y, 10) ;

  char *hash =  (char*)calloc(2, sizeof(char)) ;
  hash[0] = '#';
  hash[1] = '\0' ;

  str_x = strcat(str_x, hash)  ;
  str_x = strncat(str_x, str_y, strlen(str_y))  ;

  return str_x ;
}


void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {       
            char t = *(str + start) ;
            *(str + start) = *(str + end);
            *(str + end) = t;
            start++;
            end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = false;
 
    if (num == 0)
    {
            str[i++] = '0';
            str[i] = '\0';
            return str;
        }
 
    if (num < 0 && base == 10)
    {
            isNegative = true;
            num = -num;
        }
 
    while (num != 0)
    {
            int rem = num % base;
            str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
            num = num/base;
        }
 
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; 
 
    reverse(str, i);
 
    return str;
}

int myAtoi(char *str)
{
    int res = 0; 
 
    for (int i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';
 
    return res;
}
