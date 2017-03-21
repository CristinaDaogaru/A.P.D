package inmultire;

import java.util.concurrent.TimeUnit;
import inmultire.ThreadPool;
public class MainApp {

	public static int dimensiuneMatrice = 2;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		long startTime = System.currentTimeMillis();
		
		int [][] matriceRezultat = new int[dimensiuneMatrice][dimensiuneMatrice];
		
		GenerareMatrice generareMatrice = new GenerareMatrice(3);
		int [][] matriceUnu = generareMatrice.generareValoriMatriceRandom();
		int [][] matriceDoi = generareMatrice.generareValoriMatriceRandom();
	
		ThreadPool threadPool = new ThreadPool(2);

		
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
		{
				for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
				{
					InmultireMatrice inmultire = new InmultireMatrice(dimensiuneMatrice, matriceUnu, matriceDoi, matriceRezultat, linie, coloana);
					
					threadPool.execute(inmultire);

				}
		}
		
	long endTime = System.currentTimeMillis();
	        System.out.println("Produsul calculat in " + (endTime - startTime) + " millisecunde");
	        System.out.println("prima matrice");
	        for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
			{
					for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
					{
						System.out.print( matriceUnu[linie][coloana] + " ");
					}
					System.out.println();
			}
	        System.out.println("a doua matrice");
	        for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
			{
					for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
					{
						System.out.print( matriceDoi[linie][coloana] + " ");
					}
					System.out.println();
			}
	        System.out.println("Rezultat : " );
			for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
			{
					for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
					{
						System.out.print( matriceRezultat[linie][coloana] + " ");
					}
					System.out.println();
			}
			
			
		
	}

}
