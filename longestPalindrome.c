#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int lpd(char *str, int p, int q, int **t) {
	
	if (t[p][q] != 0) {
		return t[p][q] ;
	}else if(p == q){
		t[p][q] = 1 ; 
	}else if( str[p] == str[q] && p+1 == q){
		t[p][q] = 2;
	}
	else{
		if ( str[p] == str[q] ) {
			t[p][q] = 2 +  lpd(str, p+1, q-1, t) ;
		}else{
			
			int m1 = lpd(str, p, q-1, t) ;
			int m2 = lpd(str, p+1, q, t) ;

			t[p][q] =  m1>m2?m1:m2;
		}
	}

	return t[p][q] ;
}

int PalindromeLengthPuzzle( char *input1[] ){
	if(input1 == NULL) {
		return 0 ;
	}
	int length =  0;
	int i  = 0 ;

	while(input1[length] != NULL) {
		length = length + 1 ;
	}

	char *str = (char *)calloc((length + 1), sizeof(char) ) ;

	while(i < length ) {
		str[i] = input1[i][0] ;
		i = i + 1 ;
	}
	str[length] = '\0' ;
	
	int **arr = (int **) calloc(length , sizeof(int*)) ;
	for(i=0; i < length; i++) {
		*(arr + i) = (int *) calloc(length, sizeof(int)) ;
	}

	 return lpd(str, 0, strlen(str) - 1, arr ) ;
}

int main() {
 	
//	char *names[] = {"Bharti", "Bharat", "Akash","Bhavya", "Chand", "Brijesh", "Chetak", "Arvind", "Bhavna",  NULL} ;
//	char *names[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "D", "S", "I", "U", "V", "W", "X", "D", "B", NULL } ;
	char *names[] = {"A", "X",  "X", NULL} ;
	int l = PalindromeLengthPuzzle(names)	 ;
	printf("\n %d \n", l) ;
	return 0 ;
}
