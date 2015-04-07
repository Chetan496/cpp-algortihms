
public class RatSurface {
	
	private class RatPosition {
		
		private int x ;
		private int y;
		
		RatPosition(int x, int y){	
			this.x = x;
			this.y = y;
		}

		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder() ;
			sb.append(x).append("#").append(y) ;
			return sb.toString() ;
		}
		
	}
	
	private enum Direction {UP,RIGHT,LOWER,LEFT,NODIR};
	
	public static Direction bestDir(Integer[][] T, int maxX, int maxY, int x, int y) {
		
		int INFINITY = 1000 ;
		int del_left, del_right, del_lower, del_up ;
		Direction d = Direction.NODIR ;
		
		if ( (y - 1) == 0 ) {
			del_left = INFINITY ;
		}else{
			del_left = Math.abs( T[x][y].intValue() - T[x][y-1].intValue() ) ;
		}
		
		if ( (y + 1) == (maxY + 1) ) {
			del_right = INFINITY ;
		}else{
			del_right = Math.abs( T[x][y].intValue() - T[x][y+1].intValue() ) ;
		}
		
		if ( (x - 1) == 0 ) {
			del_up = INFINITY ;
		}else{
			del_up = Math.abs( T[x][y].intValue() - T[x-1][y].intValue() ) ;
		}
		
		if ( (x + 1) == (maxX + 1) ) {
			del_lower = INFINITY ;
		}else{
			del_lower = Math.abs( T[x][y].intValue() - T[x+1][y].intValue() ) ;
		}
		
		int temp[] = {del_left, del_lower, del_right, del_up} ;
		
		int i, minIndex=0, min;
		min = temp[0] ;
		for (i=1 ; i < temp.length ; i++) {
			
			if(temp[i] <= min){
				min = temp[i];
				minIndex = i;
			}
		}
		
		if (min == INFINITY) {
			d = Direction.NODIR ;
		}
		else if (minIndex == 0) {
			d =  Direction.LEFT ;
		}
		else if (minIndex == 1) {
			d = Direction.LOWER ;
		}
		else if (minIndex == 2) {
			d = Direction.RIGHT ;
		}
		else if (minIndex == 3) {
			d = Direction.UP ;
		}
		
		return d ;
		
	}
	
	public static void move(RatPosition position, Direction d) {
			
			if(d == Direction.NODIR){
				return;
			}
			else if(d == Direction.UP) {
				position.x = position.x - 1;
				return ;
			}
			else if (d == Direction.RIGHT) {
				position.y = position.y + 1;
				return;
			}
			else if (d == Direction.LOWER) {
				position.x = position.x + 1;
				return;
			}else{
				position.y = position.y - 1;
			}
	}
	
	public static void moveRat(RatPosition position, Integer[][] T, int maxX, int maxY) {
		Direction d = bestDir(T, maxX, maxY, position.x, position.y) ;
		move(position, d) ;
	}
	
	public static String[] RatPostion(String[] input1, String[] input2, int input3) {
		
		
		int numOfRats = input1.length ;
		if (numOfRats == 0) {
			return null ;
		}
		RatSurface ratSurface = new RatSurface() ;
		String ratPositions[] = new String[input1.length] ;
		int i = 0, j = 0;
		int maxX = input2.length ;
		int maxY = input2[0].split("#").length ;
		Integer[][] T = new Integer[maxX + 1][maxY + 1] ; //to store the temperatures of each co-ordinate
		
		
		RatPosition ratList[] = new RatPosition[numOfRats] ;
		for(String str : input1) {
			String[] tokens = str.split("#") ;
			ratList[i++] = ratSurface.new RatPosition(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1])) ;
		}
		
		
		String st;
		String tokens[] = new String[maxY]; 
		for(j = 0 ; j < (maxY + 1); j++ ) {
			
			T[0][j] = new Integer(0) ;
		}
		
		for(i = 0 ; i < (maxX + 1); i++ ) {
			
			T[i][0] = new Integer(0) ;
		}
		
		for(i = 1 ; i < (maxX+1) ; i++) {
			 st = input2[i-1] ;
			 tokens = st.split("#") ;
			
			j = 1;	
			for (String token : tokens) {
				T[i][j++] = new Integer(Integer.parseInt(token)) ;
			}
			
		}
		
		
		for ( i = 0; i < input3 ; i++) {
			
			for (RatPosition position : ratList) {
				moveRat(position, T, maxX, maxY);
			}
		}
		
		for( i = 0 ; i < ratList.length ; i++) {
			ratPositions[i] = ratList[i].toString() ;
		}
		return ratPositions ;
		
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//String input1[] = {"1#1", "2#5", "3#3", "6#3"} ;
		//String input2[] = {"2#6#8#6#-7", "2#5#-5#-5#0", "-1#3#-8#8#7", "3#2#0#6#9", "2#1#-4#5#8", "-5#6#7#4#7"} ;
		
		String input1[] = {"1#1"} ;
		String input2[] = {"7"} ;
		int steps  = 3 ;
		
		RatPostion(input1, input2 , steps) ;
		

	}

}
