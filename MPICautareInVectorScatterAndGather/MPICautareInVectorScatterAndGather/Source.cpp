#include<iostream>
#include<vector>
#include<algorithm> 
#include<mpi.h>


#define NrTotalElemente 24

using namespace std;


int main(int argc, char* argv[])
{
	const int nrCautat = 5;

	int eroare;
	int nrThreduri;
	int sirElemente[NrTotalElemente];
	int rezultatFinal[NrTotalElemente];
	const int datatag = 43;

	eroare = MPI_Init(&argc, &argv);
	if (eroare != MPI_SUCCESS)
	{
		cout << "Error starting MPI program. Terminating.\n";
		MPI_Abort(MPI_COMM_WORLD, eroare);
	}

	int idThred;
	MPI_Comm_rank(MPI_COMM_WORLD, &idThred);

	if (idThred == 0)
	{
	
		for (int i = 0; i < NrTotalElemente; i++)
		{
			sirElemente[i] = rand() % 10;
			cout << sirElemente[i] << " ";
		}
		cout << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Comm_size(MPI_COMM_WORLD, &nrThreduri);

	
	int sirElPrimitePeThred[NrTotalElemente];
	int rezultatPartial[NrTotalElemente];
	vector<int> threduri;
	for (int i = 0; i < NrTotalElemente; i++)
	{
		sirElPrimitePeThred[i] = -1;
		rezultatPartial[i] = -1;
		rezultatFinal[i] = -1;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(sirElemente, NrTotalElemente / nrThreduri, MPI_INT, sirElPrimitePeThred, NrTotalElemente / nrThreduri, MPI_INT, 0, MPI_COMM_WORLD);

	int pozitie = 0;
	for (int i = 0; i < NrTotalElemente / nrThreduri; i++)
	{
	
		if (sirElPrimitePeThred[i] == nrCautat)
		{
			rezultatPartial[pozitie] = i + (NrTotalElemente / nrThreduri) * idThred;
			pozitie++;
			
		}

	}

	MPI_Barrier(MPI_COMM_WORLD);

	for (int i = 0; i < pozitie; i++)
	{
		cout << "Process: " << idThred << " gasit: " << rezultatPartial[i]<<"\n";
	}
	cout << endl;

	MPI_Gather(rezultatPartial, NrTotalElemente/nrThreduri, MPI_INT, rezultatFinal, NrTotalElemente / nrThreduri, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	if (idThred == 0)
	{

		for (int i = 0; i < NrTotalElemente; i++)
		{
			if(rezultatFinal[i]>=0)
				cout << "Gasit la pozitia " << rezultatFinal[i] << "\n";
			
		}
	}

	MPI_Finalize();
	return 0;
}
