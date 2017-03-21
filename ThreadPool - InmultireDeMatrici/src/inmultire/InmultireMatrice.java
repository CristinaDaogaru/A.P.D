package inmultire;

public class InmultireMatrice implements Runnable {

	private int dimensiuneMatrice ;
	private int [][] matriceUnu;
	private int [][] matriceDoi;
	private int [][] matriceRezultat;
	
	private int linie;
	private int coloana;
	
	public InmultireMatrice(int dimensiuneMatrice, int[][] matriceUnu, int[][] matriceDoi, int[][] matriceRezultat,
			 int linie, int coloana) {
		
		this.dimensiuneMatrice = dimensiuneMatrice;
		this.matriceUnu = matriceUnu;
		this.matriceDoi = matriceDoi;
		this.matriceRezultat = matriceRezultat;
		this.linie = linie;
		this.coloana = coloana;
		
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		for(int indice = 0 ; indice < dimensiuneMatrice ; indice++)
		{
			matriceRezultat[linie][coloana] += matriceUnu[linie][indice] * matriceDoi[indice][coloana];
		}
		
	}
	
	
	
	
}
