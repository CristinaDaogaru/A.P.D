package inmultireMatrice;

import java.util.Random;

public class GenerareMatrice {

	private int dimensiuneMatrice;
	
	private int [][] matrice;

	public GenerareMatrice(int dimensiuneMatrice) {
		
		this.dimensiuneMatrice = dimensiuneMatrice;
	}
	
	public int[][] generareValoriMatriceRandom()
	{
		Random rand = new Random();
		matrice = new int[dimensiuneMatrice][dimensiuneMatrice];
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++){
			
			for( int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
			{
				matrice[linie][coloana] = rand.nextInt(10);
			}
		}
		return matrice;
	}
	
	
	
}
