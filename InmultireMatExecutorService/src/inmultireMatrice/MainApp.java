package inmultireMatrice;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class MainApp {

	public static int dimensiuneMatrice = 3;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		long startTime = System.currentTimeMillis();
		
		int [][] matriceRezultat = new int[dimensiuneMatrice][dimensiuneMatrice];
		
		GenerareMatrice generareMatrice = new GenerareMatrice(3);
		int [][] matriceUnu = generareMatrice.generareValoriMatriceRandom();
		int [][] matriceDoi = generareMatrice.generareValoriMatriceRandom();
		
		ExecutorService executor = Executors.newFixedThreadPool(3);
		
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
		{
				for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
				{
					executor.submit(new InmultireMatrice(dimensiuneMatrice, matriceUnu, matriceDoi, matriceRezultat, linie, coloana));
				}
		}
		
		executor.shutdown();
		
		try {
			
			executor.awaitTermination(1, TimeUnit.DAYS);
			
			long endTime = System.currentTimeMillis();
	        System.out.println("Produsul calculat in " + (endTime - startTime) + " millisecunde");
	        System.out.println("Rezultat : " );
			for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
			{
					for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
					{
						System.out.print( matriceRezultat[linie][coloana] + " ");
					}
					System.out.println();
			}
			
			
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
