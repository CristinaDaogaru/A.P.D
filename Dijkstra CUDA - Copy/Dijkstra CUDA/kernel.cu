
#include <stdio.h>


#define NUMAR_NODURI 500 

#define NUMAR_MUCHII 500 

#define COST_MAXIM 1000000

typedef struct
{
	int nod1;
	int nod2;
} Muchie;

typedef struct
{
	int nodId;
	bool vizitat;
} Nod;

//Gaseste costul drumului de la nodul start la nodul stop
__device__ __host__ int CautareMuchie(Nod start, Nod stop, Muchie *muchii, int *costuri)
{
	for (int i = 0; i < NUMAR_MUCHII; i++)
		if (muchii[i].nod1 == start.nodId && muchii[i].nod2 == stop.nodId)
			return costuri[i];
	
	return COST_MAXIM;
}

//Cauta nodurile adiacente si calculeaza costul
__global__ void Cauta_Nod(Nod *noduri, Muchie *muchii, int *costuri, int *costTemporal, int *costFinal)
{
	int nod = threadIdx.x;
	if (noduri[nod].vizitat == false)
	{
		noduri[nod].vizitat = true;
		for (int n = 0; n < NUMAR_NODURI; n++)
		{
			//Cauta costul muchiei
			int cost = CautareMuchie(noduri[nod], noduri[n], muchii, costuri);

			//ia costul minim
			if (costFinal[n] > costTemporal[nod] + cost && cost < COST_MAXIM)
				costFinal[n] = costTemporal[nod] + cost;
		}
	}
}

//Retine distanta cea mai mica
__global__ void UpdateCostDrumuri(Nod *noduri, int *costuriTemporale, int *costuriFinale)
{
	int nod = threadIdx.x;
	if (costuriTemporale[nod] > costuriFinale[nod])
	{
		costuriTemporale[nod] = costuriFinale[nod];
		noduri[nod].vizitat = false;
	}
	costuriFinale[nod] = costuriTemporale[nod];
}

void Afisare(int *costuri)
{
	FILE *output = fopen("out.txt", "w");
	for (int i = 0; i < NUMAR_NODURI; i++)
		fprintf(output, "Costul minima la nodul: %d este %d\n", i, costuri[i]);
}

int main()
{
	Nod *noduri;
	Muchie *muchii;
	int *costuri;
	int *costuriMinime, *costuriMinimeTemporale;

	Nod *d_noduri;
	Muchie *d_muchii;
	int *d_costuri;
	int *d_costuriMinime;
	int *d_costuriMinimeTemporale;

	//Creaza timerele

	float runningTime;
	cudaEvent_t timeStart, timeEnd;
	cudaEventCreate(&timeStart);
	cudaEventCreate(&timeEnd);

	//Alocare variabile host
	noduri = (Nod *) malloc(sizeof(Nod) * NUMAR_NODURI);
	muchii = (Muchie *) malloc(sizeof(Muchie) * NUMAR_MUCHII);
	costuri = (int *) malloc(NUMAR_MUCHII * sizeof(int));
	costuriMinime = (int *)malloc(NUMAR_NODURI * sizeof(int));
	costuriMinimeTemporale = (int *)malloc(NUMAR_NODURI * sizeof(int));

	//Alocare variabile device
	cudaMalloc((void**)&d_noduri, sizeof(Nod) * NUMAR_NODURI);
	cudaMalloc((void**)&d_muchii, sizeof(Muchie) * NUMAR_MUCHII);
	cudaMalloc((void**)&d_costuri, NUMAR_MUCHII * sizeof(int));
	cudaMalloc((void**)&d_costuriMinime, NUMAR_NODURI * sizeof(int));
	cudaMalloc((void**)&d_costuriMinimeTemporale, NUMAR_NODURI * sizeof(int));

	//Initializare vector noduri
	for (int i = 0; i < NUMAR_NODURI; i++)
	{
		Nod a;
		a.nodId = i;
		a.vizitat = false;
		noduri[i] = a;
	}

	//Citire input
	FILE *file = fopen("inp.txt", "r");
	for ( int i = 0; i < NUMAR_MUCHII; i++)
	{
		int nod1, nod2, cost;
		fscanf(file, "%d%d%d", &nod1, &nod2, &cost);
		Muchie e;
		e.nod1 = --nod1;
		e.nod2 = --nod2;
		muchii[i] = e;
		costuri[i] = cost;
	}
	
	//Dijkstra Algorithm
	Nod root = { 0, false };	//nod initial
	root.vizitat = true;

	costuriMinime[root.nodId] = 0;
	costuriMinimeTemporale[root.nodId] = 0;

	//Gaseste drumurile initiale din nodul de start
	for (int i = 0; i < NUMAR_NODURI; i++)
	{
		if (noduri[i].nodId != root.nodId)
		{
			costuriMinime[noduri[i].nodId] = CautareMuchie(root, noduri[i], muchii, costuri);
			costuriMinimeTemporale[noduri[i].nodId] = costuriMinime[noduri[i].nodId];
		}
		else
			noduri[i].vizitat = true;
	}

	//Copiaza variabilele pe device
	cudaMemcpy(d_noduri, noduri, sizeof(Nod) * NUMAR_NODURI, cudaMemcpyHostToDevice);
	cudaMemcpy(d_muchii, muchii, sizeof(Muchie) * NUMAR_MUCHII, cudaMemcpyHostToDevice);
	cudaMemcpy(d_costuri, costuri, NUMAR_MUCHII * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_costuriMinime, costuriMinime, NUMAR_NODURI * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_costuriMinimeTemporale, costuriMinimeTemporale, NUMAR_NODURI * sizeof(int), cudaMemcpyHostToDevice);

	clock_t t;
	t = clock();

	//Executia paralela
		Cauta_Nod <<< 1, NUMAR_NODURI >>>(d_noduri, d_muchii, d_costuri, d_costuriMinime, d_costuriMinimeTemporale);
		//for (int j = 0; j < V; j++)
			UpdateCostDrumuri <<< 1, NUMAR_NODURI >>>(d_noduri, d_costuriMinime, d_costuriMinimeTemporale);
	

	//calculeaza timpul

	t = clock() - t;
	printf("Timpul de executie este: %f ms\n", ((double)t) / CLOCKS_PER_SEC);

	//Copiaza rezultatul inapoi pe device
	cudaMemcpy(costuriMinime, d_costuriMinime, NUMAR_NODURI * sizeof(int), cudaMemcpyDeviceToHost);

	Afisare(costuriMinime);

	free(noduri);
	free(muchii);
	free(costuri);
	free(costuriMinime);
	free(costuriMinimeTemporale);

	cudaFree(d_noduri);
	cudaFree(d_muchii);
	cudaFree(d_costuri);
	cudaFree(d_costuriMinime);
	cudaFree(d_costuriMinimeTemporale);

	cudaEventDestroy(timeStart);
	cudaEventDestroy(timeEnd);
	getchar();
}