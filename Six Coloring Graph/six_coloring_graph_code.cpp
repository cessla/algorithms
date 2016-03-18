//  // 1 // czytanie i zapis standardowego wej≈?cia/wyj≈?cia
//  // 2 // czytanie i zapis pliku


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <stdio.h>
#include <fstream>

using namespace std;

struct vertex	// struktura do opisu wierzcho≈?ka
{
	int index;
	int color;
	set<int>* nbr;		// wska≈∫nik do listy (wektora) sƒ?siad√≥w
};


int heap_size;		// ilo≈?ƒ? element√≥w w kolejce priorytetowej

vector<struct vertex> E;		// kontener na graf, E[index], gdzie index - numer wierzcho≈?ka,
vector<struct vertex> S;		// kontener na podgraf powsta≈?y po usuniƒ?ciu wierzcho≈?ka
struct vertex* queue[100000];		// tablica wska≈∫nik√≥w na elementy kolejki priorytetowej	
vector<struct vertex*> K;		// kontener wska≈∫nik√≥w do wierzcho≈?k√≥w wg rosnƒ?cych stopni

// funkcje do os≈?ugi kolejki priorytetowej przez za pomocƒ? kopca
void min_heap_fix ( int, struct vertex** );
void heap_remove (struct vertex**);
void heap_insert (struct vertex*, struct vertex** );
struct vertex* temp = new struct vertex;


int main()
{
	// 2 //
	//ifstream infile("input1");		// plik z danymi testowymi
	//ofstream outfile("output1");	// plik z odpowiedziƒ?
	
	int t, n, m, v, u;			// t -liczba test√≥w, n - liczba wierzcho≈?k√≥w, m - liczba krawƒ?dzi
	
	struct vertex** Q;		// wska≈∫nik do tablicy wska≈∫nik√≥w kolejki priorytetowej
	Q = *&queue;

	struct vertex *newV;
	set<int> colorSet;		// paleta dostƒ?pnych kolor√≥w 1-6
	for (int i = 1; i <= 6; i++) 
	{
		colorSet.insert(i);
	}

	// 2 //
	//string line;
	//getline(infile, line);

	// wczytanie liczby test√≥w
	scanf("%d", &t);	
	// 2//
	//sscanf(line.c_str(), "%d%*[\n]", &t);

	for ( int i = 0; i < t; i++)
	{
		heap_size = 0;
		
		// wczytanie danych 
		scanf("%*[\n]Graph with %d nodes and %d edges:", &n, &m);
		
		// 2 //
		//getline(infile, line);
		//sscanf(line.c_str(), "Graph with %d nodes and %d edges:", &n, &m);

		E.resize(n);
		S.resize(n);
		K.resize(0);
		K.reserve(n);
		for ( int i = 0; i < n; i++ )
		{
			newV = new struct vertex;
			newV -> color = -1;
			newV -> index = i;
			newV -> nbr = new set<int>;
			E[i] = *newV;
			S[i] = *newV;
			S[i].nbr = new set<int>;

			colorSet.insert(i+1);

		}
		// 2 //
		//int offset = 0;
		//int pos;
		scanf("%*[\n]");
		//getline(infile, line);
		for ( int i = 0; i < m; i++ )
		{		
			scanf("{%d,%d}%*[,]", &v, &u);
			// 2 //
			//sscanf(line.c_str() + offset, "{%d,%d}%*[,]%n", &v, &u, &pos);
			//offset += pos;
			
			(*E[v].nbr).insert(u);
			(*E[u].nbr).insert(v);

			(*S[v].nbr).insert(u);
			(*S[u].nbr).insert(v);
		}		
		
		// dodanie wska≈∫nik√≥w do wierzcho≈?k√≥w do kolejki priorytetowej
		for ( int i = 0; i < n; i++ )
		{
			newV = &S[i];
			heap_insert( newV, Q );
		}

		// sortowanie wierzcho≈?k√≥w wg stopnia
		while (heap_size > 0 )
		{
			for (std::set<int>::iterator it=(*Q[0] ->nbr).begin(); it!=(*Q[0] ->nbr).end(); ++it )
			{
				int nbr_index = *it;
				(*S[ nbr_index ].nbr).erase(Q[0] ->index);
			}
			K.push_back( &E[ Q[0]->index ] );
			(*S[ Q[0] -> index ].nbr).clear();
			heap_remove( Q );
		}
		
		// przydzielenie kolor√≥w - algorytm zach≈?anny, wierzcho≈?ki wybierane wg malejƒ?cej kolejno≈?ci z K
		for (int i = K.size()-1; i >= 0; i-- )
		{
			set<int> color(colorSet);
			for (std::set<int>::iterator it=(*K[i] ->nbr).begin(); it!=(*K[i] ->nbr).end(); ++it )
			{
				int nbr_index = *it;
				color.erase( E[ nbr_index ].color );
			}
			K[i] -> color = *color.begin();
		}

		for ( int i = 0; i < n; i++ ) 
		{
			printf("%d %d\n", E[i].index, E[i].color);
			// 2 //
			//outfile << E[i].index << " " << E[i].color << endl;
		}
		printf("\n");
		// 2 //
		//outfile << endl;
	}

	//system("PAUSE");
	// 2 //
	//infile.close();
	//outfile.close();
	return 0;
}


// funkcja do budowy i naprawiania kopca minimalizujacego
void min_heap_fix ( int i, struct vertex** Q )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int min;
	
	
	if ( left <= heap_size && (*Q[left]->nbr).size() < (*Q[i]->nbr).size() )
	{
		min = left;
	}
	else
	{
		min = i;
	}

	if ( right <= heap_size && (*Q[right]->nbr).size() < (*Q[min]->nbr).size() )
	{
		min = right;
	}

	if ( min != i )
	{
		temp = Q[i];
		Q[i] = Q[min];
		Q[min] = temp;	
		min_heap_fix ( min, Q );
	}
}

 

// usuwanie min z kolejki i naprawa w≈?asno≈?ci kopca
void heap_remove ( struct vertex** Q )
{
	
	if ( heap_size > 0 )
	{
		//temp = Q[0];
		Q[0] = Q[heap_size-1];
		//delete temp; // usuwanie niepotrzebnego elementu typu struct queue
		heap_size -= 1;
		min_heap_fix (0, Q);
	}
}


// wstawianie do kolejki i naprawa kopca
void heap_insert (struct vertex* elem, struct vertex** Q )
{
	heap_size += 1;
	int i = heap_size-1;

	while ( i > 0 && (*elem -> nbr).size() < (*Q[(i-1)/2] -> nbr).size() )
	{
		Q[i] = Q[(i-1)/2] ;
		i = ( i-1 )/2;
	}

	Q[i] = elem;
}

