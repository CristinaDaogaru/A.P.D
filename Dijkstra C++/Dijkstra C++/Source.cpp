
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>

#define NUMAR_NODURI 500
#define NUMAR_MUCHII 500

using namespace std;

//functia care gaseste distanta minima dintre noduri nevizitate inca
long long distantaMinima(vector<long long> dist, vector<bool> vizitat)
{
	// Initialize min value
	long long minim = LONG_MAX, indexMinim;

	for (int nod = 0; nod < NUMAR_NODURI; nod++)
		if (vizitat[nod] == false && dist[nod] <= minim)
			minim = dist[nod], indexMinim = nod;

	return indexMinim;
}


void printSolution(vector<long long> dist)
{
	ofstream out("output.txt");
	out<<"Nodul distanta de la nodul de start\n";
	for (long long i = 0; i < NUMAR_NODURI; i++)
		out<< i<< "\t\t"<< dist[i]<< endl;
}

// Funtie care implementeaza alg gasint distanta minima
void dijkstra(vector<vector<int>> graph, long long start)
{
	vector<long long> dist(NUMAR_NODURI, INT_MAX); //retine distanta minima

	vector<bool> vizitate(NUMAR_NODURI); 

	dist[start] = 0;

	// gasire distanta minima
	for (long long count = 0; count < NUMAR_NODURI - 1; count++)
	{

		long long muchie = distantaMinima(dist, vizitate);

		vizitate[muchie] = true;

		for (long long nod = 0; nod < NUMAR_NODURI; nod++)

			if (!vizitate[nod] && graph[muchie][nod] && dist[muchie] != INT_MAX && dist[muchie] + graph[muchie][nod] < dist[nod])
				
				dist[nod] = dist[muchie] + graph[muchie][nod];
	}

	printSolution(dist);
}

int main()
{
	vector<vector<int>> graph(NUMAR_NODURI, vector<int>(NUMAR_NODURI, 0));

	ifstream file("input.txt");
	for (long long i = 0; i < NUMAR_MUCHII; i++)
	{
		long long nod1, nod2, cost;
		file >> nod1 >> nod2 >> cost;
		graph[nod1][nod2] = cost;
		graph[nod2][nod1] = cost;
	}

	clock_t t;
	t = clock();

	dijkstra(graph, 0);
	t = clock() - t;

	cout << " execution time: " << ((double) t ) / CLOCKS_PER_SEC << endl;
	cout << "\n\n END";
	getchar();
	return 0;
}