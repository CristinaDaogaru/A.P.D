package inmultireMatrice;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import com.sun.xml.internal.ws.config.management.policy.ManagementAssertionCreator;

public class MainApp {

	public static int dimensiuneMatrice = 3;
	
	public static void main(String[] args) throws InterruptedException {
		// TODO Auto-generated method stub
		long startTime = System.currentTimeMillis();
		
		int [][] matriceRezultat = new int[dimensiuneMatrice][dimensiuneMatrice];
		
		GenerareMatrice generareMatrice = new GenerareMatrice(3);
		int [][] matriceUnu = generareMatrice.generareValoriMatriceRandom();
		int [][] matriceDoi = generareMatrice.generareValoriMatriceRandom();
		System.out.println("Prima matrice : ");
		
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
		{
			
				for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
				{
					System.out.print(matriceUnu[linie][coloana] + " ");
				}
				System.out.println();
		}
		System.out.println("A doua matrice : ");
		
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
		{
			
				for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
				{
					System.out.print(matriceDoi[linie][coloana] + " ");
				}
				System.out.println("\n");
		}
			
	
		Evaluator evaluator = new Evaluator();
		evaluator.evaluareSolutii(dimensiuneMatrice, matriceUnu, matriceDoi, matriceRezultat);
		
		long endTime = System.currentTimeMillis();
		
		System.out.println("\nProdusul calculat in " + (endTime - startTime) + " millisecunde");
		
	}

}
