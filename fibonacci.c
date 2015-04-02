#include<stdio.h>
#include<stdlib.h>

/*
 * This betterfib function works nicely without any delay for fibonacci numbers upto 92
 * Is fast!! But after 92 it does give incorrect results
 *
 * Seems like unsigned long long int is not enough to store the huge numbers
 *
 */

unsigned long long int betterfib(int n, unsigned long long int *arr) {
		/* check if fib(n-1) and fib(n-2) are already available in our cache */
	unsigned long long int temp = 0 ;
	if ( n < 2) {
		return 1;
	}else if( arr != NULL && *(arr+n - 1) != 0 ){
		
			return *(arr + n - 1) ;
	}
	else{
		temp = betterfib(n-1, arr) + betterfib(n-2, arr) ;
	        *(arr + n - 1) = temp ;
	        return temp;
	}
	
}
int main(){
  	int fibTerm = 92;
	unsigned long long int result = 0;
        unsigned long long int *arr = (unsigned long long int*) calloc(fibTerm, sizeof(unsigned long long int)) ;
	result = betterfib(fibTerm, arr) ;

	printf("\n The %dth term of the fibonacci series is %llu \n ", fibTerm, result);
	return 0;
}
