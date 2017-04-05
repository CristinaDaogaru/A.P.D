# include <iostream>
#include "mpi.h"

using namespace std;



int main(int argc, char *argv[])
{
	int nrTotalElemente = 24;
	int nrThreaduri;
	int idThread;
	int error;
	int lungimeInterval;
	int start;
	int stop;


	error = MPI_Init(&argc, &argv);

	if (error != MPI_SUCCESS) {
		cout << "Error starting MPI program. Terminating.\n";
		MPI_Abort(MPI_COMM_WORLD, error);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &nrThreaduri);
	MPI_Comm_rank(MPI_COMM_WORLD, &idThread);

	MPI_Bcast(&nrTotalElemente, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	lungimeInterval = nrTotalElemente / nrThreaduri;

	if (lungimeInterval * idThread == 0)
		start = 2;
	else
		start = lungimeInterval * idThread;
	stop = lungimeInterval * idThread + lungimeInterval;

	for (int nr = start; nr < stop; ++nr)
	{
		bool nrPrim = true;
		for (int div = 2; div <= nr / 2; ++div)
			if (nr % div == 0)
			{
				nrPrim = false;
				break;
			}
		if (nrPrim)
			cout << "Numarul prim: " << nr << " gasit de thread-ul : " << idThread << endl;
	}

	MPI_Finalize();
}

