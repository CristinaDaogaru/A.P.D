#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include <omp.h>

using namespace std;

int dimensiuneMatrice = 2;


vector<vector<double>>  generareValoriMatriceRandom()
{
	vector<vector<double>> matrice(dimensiuneMatrice, vector<double>(dimensiuneMatrice)) ;

	for (int linie = 0; linie < dimensiuneMatrice; linie++)
	{
		for (int coloana = 0; coloana < dimensiuneMatrice; coloana++)
		{
			matrice[linie][coloana] = rand() % 10 ;
		}
	}
	return matrice;

}

vector<vector<double>> Inmultire(vector<vector<double>> matrice1, vector<vector<double>> matrice2 )
{
	vector<vector<double>> matriceRezultat(dimensiuneMatrice,vector<double>(dimensiuneMatrice)) ;
	
	omp_set_num_threads(2);
	#pragma omp parallel for default(none) shared( matrice1, matrice2, matriceRezultat ) //private(row)
	for (int linie = 0; linie < dimensiuneMatrice; linie++)
	{
		for (int coloana = 0; coloana < dimensiuneMatrice; coloana++)
		{
			matriceRezultat[linie][coloana] = 0;

			for (int indice = 0; indice < dimensiuneMatrice; indice++)
			{
				matriceRezultat[linie][coloana] += matrice1[linie][indice] * matrice2[indice][coloana];
			}
		}
	}
	return matriceRezultat;
}

int main()
{

	long startTime;

	vector<vector<double>> matriceRezultat(dimensiuneMatrice, vector<double>(dimensiuneMatrice));
	
	vector<vector<double>> matrice1 = generareValoriMatriceRandom();
	vector<vector<double>> matrice2 = generareValoriMatriceRandom();

	

	cout << "Prima Matrice:\n";
	for (int linie = 0; linie < matrice1.size(); linie++)
	{
		for (int coloana = 0; coloana < matrice1.size(); coloana++)
		{
			cout << matrice1[linie][coloana] << "  ";
		}
		cout << endl;
	}

	cout << "A doua matrice:\n";
	for (int linie = 0; linie < matrice2.size(); linie++)
	{
		for (int coloana = 0; coloana < matrice2.size(); coloana++)
		{
			cout << matrice2[linie][coloana] << "  ";
		}
		cout << endl;
	}

	matriceRezultat = Inmultire(matrice1, matrice2);
	cout << "MatriceRezultat:\n";
	for (int linie = 0; linie < matriceRezultat.size(); linie++)
	{
		for (int coloana = 0; coloana < matriceRezultat.size(); coloana++)
		{
			cout << matriceRezultat[linie][coloana] << "  ";
		}
		cout << endl;
	}

	getchar();

	return 0;

}
