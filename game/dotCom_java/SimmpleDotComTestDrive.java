public class SimmpleDotComTestDrive{
	public static void main(String[]args){
		int numOfGuess = 0;
		GameHelper helper = new GameHelper();

		SimpleDotCom theDotCom = new SimpleDotCom();
		int randomNum = (int)(Math.random()*5);

		int[] locations = {randomNum,randomNum+1,randomNum+2};
		theDotCom.setLocationCells(locations);
		boolean isAlive = true;

		while (isAlive == true){
			String guess = helper.getUserInput("enter a number");
			String result = theDotCom.cheakYourself(guess);
			numOfGuess++;
			if(result.equals("kill")){
				isAlive = false;
				System.out.println("you took" + numOfGuess +"guesses");	
			}
		}


	}
}

	/*SimpleDotCom dot = new SimpleDotCom();

	int[] locations={2,3,4};
	dot.setLocationCells(locations);

	String userGuess= "2";
	String result = dot.cheakYourself(userGuess);
	}

}*/