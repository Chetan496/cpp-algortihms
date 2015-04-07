#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define true 1
#define false 0

#define INFINITY 1000

typedef struct Pos_t
{
   int x;
   int y;
} Pos_t ;

typedef struct Pos_t *Pos_p ;

typedef struct Rat_t
{
   Pos_p pos ;
} Rat_t ;

typedef struct Rat_t *Rat_p ;

typedef enum Dir
{ 
  UP,
  RIGHT,
  LOWER,
  LEFT,
  NODIR
} Dir;

int abs_value(int t1, int t2) ;

int change_in_temp(int **T, int x1, int y1, int x2, int y2 )  ;

Dir bestDirToMove(int **T, int maxX, int maxY, Pos_p pos) ;

void move(Rat_p rat, Dir dir) ;

void moveRat(Rat_p rat, int **T, int maxX, int maxY) ;

Pos_p initializePos(int x, int y ) ;

int **initializeTemp(char **strArray) ;

Rat_p initializeRat(Pos_p p) ;

Rat_p initializeRatFromStr(char *str) ;

char *getPosAsStr(Pos_p p) ;

Pos_p getPosFromStr(char *str) ;

void reverse(char *str, int length) ;

char *itoa(int num, char *buffer, int base) ;

int myAtoi(char *str) ;

int *getIntsFromTempString(char *str) ;

int getLengthOfStrArray(char **str) ;

int getMaxY(char *str) ;

char** RatsPostions(char* input1[], char* input2[], int input3)
{	
	int numOfRats = getLengthOfStrArray(input1) ;
	int i = 0, j = 0  ;
	int maxX = getLengthOfStrArray(input2); 
	int maxY = getMaxY(input2[0]) ;
	char **finalRatPos  = (char **)calloc(numOfRats+1, sizeof(char *)) ;
	Rat_p *rats = (Rat_p *)calloc(numOfRats, sizeof(Rat_p)) ;
	for (i = 0; i < numOfRats; i++) 
        {
		rats[i] = initializeRatFromStr(input1[i]) ;		
	}

	int **T = initializeTemp(input2) ;
	for( i = 0; i < input3; i++ )
        {
		for ( j = 0; j < numOfRats; j++)
                {
			moveRat(rats[j], T, maxX, maxY) ;
		}
	}

	for (i = 0; i < numOfRats; i++)
        {
		finalRatPos[i] = getPosAsStr(rats[i]->pos) ;		
	}	
	
	finalRatPos[i] = NULL ;

	return finalRatPos ;
}

int abs_value(int t1, int t2)
{
   int diff = t1 - t2 ;
   return ( ( diff < 0 ) ? (-1 * diff) : diff  ) ;
}

int change_in_temp(int **T, int x1, int y1, int x2, int y2) 
{
   return (abs_value( T[x1][y1], T[x2][y2] ) ) ;

}

Dir bestDirToMove(int **T, int maxX, int maxY,  Pos_p pos ) 
{
   int x = pos->x;
   int y = pos->y ;
   int del_left, del_right, del_up, del_lower ;
   Dir d;
   if (  (y-1) == 0   )
   {
      del_left = INFINITY ;
   }
   else
   {
      del_left = change_in_temp( T, x, y, x, y-1 ) ;
   }
   
   if ( (y+1) == (maxY + 1) ) 
   {
      del_right = INFINITY ;
   }
   else
   {
      del_right = change_in_temp(T, x, y, x, y+1) ;
   }
   
   if ( (x-1) == 0 )
   {
      del_up = INFINITY ;
   }
   else
   {
      del_up = change_in_temp(T, x, y, x-1 , y) ;
   }
   
   if ( (x+1) == (maxX + 1) )
   {
      del_lower = INFINITY;
   }
   else
   {
      del_lower = change_in_temp(T, x, y, x+1, y) ;
   }

   int *t = (int *)calloc(4, sizeof(int)) ;
   t[0] = del_left ;
   t[1] = del_lower;
   t[2] = del_right ;
   t[3] = del_up ;
   
   int i;
   int minIndex = 0;
   int min = t[0] ;
   

   for( i = 1; i < 4; i++ ) {
      if (t[i] <= min) {
         min = t[i];
         minIndex = i ;
      }
   }
   
   if (min == INFINITY)
   {
	d = NODIR ;
	return d ;	
   }
   if(minIndex == 0)
   {
      d =  LEFT;
   }
   if(minIndex == 1)
   {
      d  = LOWER;
   }
   if(minIndex == 2) 
   {
      d =  RIGHT;
   }
   if (minIndex == 3)
   {
      d =  UP ;
   }
   
   free(t) ;
   return d;
}


void move(Rat_p rat, Dir dir)
{
   if(dir == NODIR)
   {
	return ;
   }
   if (dir == UP)
   {
      rat->pos->x = rat->pos->x - 1;
   }
   else if (dir == RIGHT)
   {
      rat->pos->y = rat->pos->y + 1 ;
   }
   else if ( dir == LOWER)
   {
      rat->pos->x = rat->pos->x + 1;
   }
   else
   { 
      rat->pos->y = rat->pos->y - 1;
   }
}

void moveRat(Rat_p rat, int **T, int maxX, int maxY)
{
	Dir d = bestDirToMove(T, maxX, maxY, rat->pos) ;
	move(rat, d) ;
}

Pos_p initializePos(int x, int y)
{
   Pos_p p = (Pos_p) calloc(1, sizeof(Pos_t)) ;
   p->x = x;
   p->y = y;
   return p ;
}

int **initializeTemp(char **strArray)
{
   int **T = NULL ;
   int rowTotal = 0,  i;
   while( strArray[rowTotal] != NULL )
   {
      rowTotal = rowTotal + 1;

   }

   T = (int **) calloc( rowTotal + 1, sizeof(int *) ) ;

   for( i=1 ; i < (rowTotal + 1) ; i++) 
   {
   
      T[i] = getIntsFromTempString( strArray[i-1] ) ;
   }

   return T ;
}

int *getIntsFromTempString(char *str) 
{
   int *arr = NULL ;
   int numOfHashes = 0, i = 0;
   char *token ;
   while(str[i] != '\0') 
   {
      if (str[i] == '#') 
      {
         numOfHashes = numOfHashes  + 1 ;
      }
      i = i + 1 ;
   }
   
   if (numOfHashes == 0) 
   {
	arr = (int *)calloc( 1, sizeof(int) ) ;
	arr[0] = myAtoi(str) ;
	return arr ;
   }
   char *str_dup = strndup(str, strlen(str)) ;
   arr = (int *)calloc( (numOfHashes + 2) , sizeof(int)) ;
   
   token = strtok(str_dup, "#") ;
   for (i=1; i < (numOfHashes + 2) ; i++) 
   {
      arr[i] = myAtoi(token) ;
      token = strtok(NULL, "#") ;

      if (token == NULL)
      {
         break ;
      }
   }
   
   if (str_dup != NULL) 
   {
	free(str_dup) ;
   }
   return arr ;
}


char *getPosAsStr(Pos_p p) 
{
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


Pos_p getPosFromStr(char *str)
{
   char *str_dup = strndup(str, strlen(str)) ;
   char *token ;
   
   token = strtok(str_dup, "#") ;
   int x = myAtoi(token) ;
   token = strtok(NULL, "#") ;
   int y = myAtoi(token) ;
   Pos_p p = initializePos(x , y) ;   
   if(str_dup != NULL) 
   {
	free(str_dup) ;
   }	
   return p ;
}

void reverse(char *str, int length)
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

char* itoa(int num, char *str, int base)
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
    {
        str[i++] = '-';
    }
 
    str[i] = '\0'; 
 
    reverse(str, i);
 
    return str;
}

int myAtoi(char *str)
{
    int res = 0;  
    int sign = 1; 
    int i = 0;  
     
    if (str[0] == '-')
    {
        sign = -1; 
        i++; 
    }
     
    for (; str[i] != '\0'; ++i)
	{
		res = res*10 + str[i] - '0';
	}
        
   
    return sign*res;
}

int getMaxY(char *str)
{   
   int numOfHashes = 0, i = 0;
   while(str[i] != '\0') 
   {
      if (str[i] == '#') 
      {
         numOfHashes = numOfHashes  + 1 ;
      }
      i = i + 1 ;
   }

   return (numOfHashes + 1) ;
}

int getLengthOfStrArray(char **str) 
{	
	if(str == NULL) {
		return 0 ;
	}
	int i = 0;
	while(str[i] != NULL) 
        {
		i = i + 1;
	}
	return i ;
}

Rat_p initializeRat(Pos_p p)
{
	Rat_p rat = (Rat_p) calloc(1, sizeof(Rat_t)) ;
	rat->pos = p ;
	return rat ;
}

Rat_p initializeRatFromStr(char *str) 
{	
	Pos_p p = getPosFromStr(str) ;
	Rat_p rat = initializeRat(p) ;
	return rat ;
}



int main(){
	char *input1[] = {"1#1", "2#5", "3#3", "6#3", NULL} ;
	char *input2[] = {"2#6#8#6#-7", "2#5#-5#-5#0", "-1#3#-8#8#7", "3#2#0#6#9", "2#1#-4#5#8", "-5#6#7#4#7", NULL} ;
	int steps = 3 ;  

	char **latestPos = RatsPostions(input1, input2, steps) ;
	return 0;
}
