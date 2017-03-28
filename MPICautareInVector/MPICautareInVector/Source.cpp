#include<iostream>
#include<vector>
#include<mpi.h>
#include <utility> 

using namespace std;

int nrTotalElemente = 500;
int nrCautat = 5;
//vector<int> sir(nrTotalElemente);
vector<pair<int, int>> rezultat;

int idThread;
int nrThreduri;

vector<int> generareRandom()
{
	vector<int> sir(nrTotalElemente);

	for (int i = 0; i < nrTotalElemente; i++) {
		int valoare = rand() % 100;
		sir[i] = valoare;
		
	}
	return sir;
}

void cautare(int inceputInterval, int sfarsitInterval)
{
	vector<int> sir = generareRandom();
	

	for (int i = inceputInterval; i < sfarsitInterval; i++){

		if (sir[i] == nrCautat){

			MPI_Comm_rank(MPI_COMM_WORLD, &idThread);
			rezultat.push_back(make_pair(i, idThread));
		}
	}
	
}

int main(int argc, char* argv[])
{
	int eroare;
	int lungimeSubinterval;

	eroare = MPI_Init(&argc, &argv);
	if (eroare != MPI_SUCCESS) {

		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, eroare);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &nrThreduri);

	lungimeSubinterval = nrTotalElemente / nrThreduri;

	MPI_Comm_rank(MPI_COMM_WORLD, &idThread);

	if (idThread < nrThreduri){

		cautare(lungimeSubinterval * idThread, lungimeSubinterval * idThread + lungimeSubinterval);
	}
	else
		cautare(lungimeSubinterval * idThread, lungimeSubinterval);

	
	
	MPI_Finalize();
	for (int i = 0; i < rezultat.size(); i++){
		cout << "Gasit la pozitia " << rezultat[i].first << " de thred-ul " << rezultat[i].second << endl;
	}

	
	
}

