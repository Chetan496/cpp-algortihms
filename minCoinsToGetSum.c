#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INFINITY 1000 //assuming that there is no coin with this value
/* *This function takes an array of coins each with a value and the sum required
  It returns the minimum number of coins needed to find that sum*/

/*eg: *v = {2,1,5}  */

typedef struct Coin_Table{
	int coinValue;   //coin value added to smaller sum to get this sum. Tis entry is stored at index (coin_table + sum)
	int smallerSum ;
} Coin_Table_t, *Coin_Table_p ;

int getMinNumOfCoins(int *v, size_t vsize,  int sum) {

	int i, j;
	int *min_arr = (int *) calloc(sum+1, sizeof(int)) ;
	Coin_Table_p coin_table_p = (Coin_Table_p) calloc(sum+1, sizeof(Coin_Table_t)) ;
	int coinValue;
	int smallerSum ;

	for (i = 0; i < sum+1; i++) {
		min_arr[i] = INFINITY ;
	}

	min_arr[0] = 0;  //trivial case  - min number of coins for a sum of 0 is 0
	
	for (  i = 1; i <= sum; i++ ) {
		
		for ( j = 0; j < vsize; j++ ) {
			
			if ( v[j] <= i &&  ( min_arr[i] > min_arr[ i - v[j] ]  )  ) {
				coinValue = v[j]			;
				smallerSum = i - v[j] ;
				min_arr[i] = min_arr[ i - v[j] ] + 1 ;
							
			}
			
		}

		coin_table_p[i].coinValue = coinValue ;
		coin_table_p[i].smallerSum = smallerSum ;
	}
	

	/* ----- Let us print the coins that will be used to get this amount*/
	i = sum ;
	while(i > 0) {
		printf("\n Coin with value  %d \n", coin_table_p[i].coinValue) ;
		i = coin_table_p[i].smallerSum ;
	}
	return min_arr[sum] ;
}

int main(){
 	int coinVals[] = {1 , 2 ,5  }	;
	int sum = 19 ;
	int x = getMinNumOfCoins(coinVals, 3, sum) ;
	printf("\n min coins needed to get sum of  %d are %d \n ", sum, x) ;
	return 0 ;
}
