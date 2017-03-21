package inmultireMatrice;

public class Evaluator {

	
	public void evaluareSolutii(int dimensiuneMatrice, int [][] matriceUnu, int[][] matriceDoi, int[][] matriceRezultat) throws InterruptedException
	{
		for(int linie = 0 ; linie < dimensiuneMatrice ; linie++ )
		{
			Thread threads;
			
				for(int coloana = 0 ; coloana < dimensiuneMatrice ; coloana++)
				{
					 threads = new Thread( new InmultireMatrice(dimensiuneMatrice, matriceUnu, matriceDoi, matriceRezultat, linie, coloana));
					 threads.start();
					
					System.out.println("Threadul " + threads.getName());
				}
				
				
		}
		
	
		System.out.println("\nRezultat : " );
		
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

