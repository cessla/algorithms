#include <vector>
#include <map>
#include <string>


using namespace std;

struct city	// struktura do opisu miasta
{
	bool visited;					// czy miasto odwiedzone
	vector<vector<int> >* nbr;		// wskaznik do listy (wektora) sasiadów
};


int heap_size;		// ilosc elementów w kolejce priorytetowej

vector<struct city> E(10001);		// kontener na miasta, E[index]: index - numer miasta,
vector<int> D(10001);		// kontener na odleglosci od punktu startowego
map<string , int> cities;	// mapa na pary miasto - index
vector<int>* queue[100000];		// tablica wskazników na elementy kolejki priorytetowej
vector<vector<int> > routes(101);		// kontener na trasy do wyznaczenia
vector <int>* temp = new vector <int>(1);		
const int INF = (1 << 30);		// nieskonczonosc

// funkcje do oslugi kolejki priorytetowej przez za pomoca kopca
void min_heap_fix ( int, vector<int>** );
void heap_remove (vector<int>**);
void heap_insert (vector <int>*, vector<int>** );

// funkcja wyznaczajaca najkrótsza sciezke
int dijkstry ( int, int, vector<int>** );

int main()
{
	
	int t, n, nb, b, c, r;			// t -liczba testów, n - liczba miast, nb - ilosc sasiednich miast, b - numer sasiedniego miasta, 
									// c - koszt dotarcia do sasiedniego miasta, r - liczba tras do wyznaczenia
	
	vector<int>** Q;		// wskaznik do tablicy wskazników kolejki priorytetowej
	Q = *&queue;
	vector<int>* newElem;
	struct city *newCity;
	vector<vector<int> >* newList;

	scanf("%d", &t);	// wczytanie liczby testów

	for ( int i = 0; i < t; i++)
	{
		char name[12];		//nazwa miasta
		char name1[12];		
		char name2[12];

		// wczytanie danych 
		
		scanf("%d", &n);	// wczytanie liczby miast
	
		for ( int i = 1; i <= n; i++ )
		{
			scanf("%s", &name);		//wczytanie nazwy miasta
			cities[string(name)] = i;	// zapisanie do mapy miasto-index

			newCity = new struct city;
			newList = new vector< vector <int> >;

			scanf("%d", &nb);	//wczytanie ilosci sasiednich miast
			for ( int j = 0; j < nb; j++ )
			{
				scanf("%d %d", &b, &c);

				vector <int> N;
				N.resize(3);
				N[0] = i;
				N[1] = b;
				N[2] = c;
				(*newList).push_back(N);
			}
			newCity -> nbr = newList;		
			E[i] = *newCity;
		}			
	
		// wczytanie szukanych tras - zamiana nazwy na index

		scanf("%d", &r);

		vector <int> route(2);
		for ( int i = 0; i < r; i++)
		{
			scanf("%s", &name1);	//wczytanie nazwy miasta poczatkowego
			scanf("%s", &name2);	//wczytanie nazwy miasta docelowego

			int start = cities.find(string(name1)) -> second;
			int end = cities.find(string(name2)) -> second;
	
			route[0] = start;
			route[1] = end;

			routes[i] = route;
		}

		// wyszukiwanie tras

		for ( int i = 0; i < r; i++)
		{
			heap_size = 0;

			for(int j = 1; j <= n; j++ ) 
			{
				D[j] = INF;
				E[j].visited = false;
			}

			int start = routes[i][0];
			int end = routes[i][1];
			
			newElem = new vector <int> (2);
			(*newElem)[0] = 0;
			(*newElem)[1] = start;

 			heap_insert ( newElem, Q );

			int sum = dijkstry( start, end, Q );
			printf("%d\n", sum);
		}
	}
	//system("PAUSE");
	return 0;
}


// funkcja do budowy  i naprawiania kopca minimalizujacego
void min_heap_fix ( int i, vector<int>** Q )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int min;
	
	
	if ( left <= heap_size && Q[left][0] < Q[i][0] )
	{
		min = left;
	}
	else
	{
		min = i;
	}

	if ( right <= heap_size && Q[right][0] < Q[min][0] )
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

 

// usuwanie min z kolejki i naprawa wlasnosci kopca
void heap_remove ( vector<int>** Q )
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
void heap_insert (vector <int>* elem, vector<int>** Q )
{
	heap_size += 1;
	int i = heap_size-1;

	while ( i > 0 && elem[0] < Q[(i-1)/2][0]  )
	{
		Q[i] = Q[(i-1)/2] ;
		i = ( i-1 )/2;
	}
	
	Q[i] = elem;
}

// funkcja realizujaca algorytm dijkstry
// kolejnosc wybierania wezlów: od min cost do max cost
int dijkstry ( int start, int end, vector<int>** Q )
{
	D[start] = 0;
	vector<int>* newElem;

	while ( E[end].visited == false )
	{
		// wyszukiwanie najmniejszego elementu, czyli pobranie min kopca
		vector <int>* curr_min = Q[0];
		int index = (*curr_min)[1];
		city* curr = &E[ index ];

		if ( curr -> visited == false ) 
		{
			curr -> visited = true;
		}
		else 
		{	
			heap_remove( Q );
			continue;
		}
	
		vector <vector <int> >* v = E[ index ].nbr;
		int v_size = (*v).size();
		for(int z = 0; z < v_size; z++) {
			if ( (E[(*v)[z][1]]).visited == true )
			{
				continue;
			} 
			else 
			{
				int nbr_index = (*v)[z][1];
				int nbr_dist = (*v)[z][2];
				
				if ( D[ index ] + nbr_dist < D[nbr_index] )
				{
					D[nbr_index] = D[ index ] + nbr_dist;
				}
				
				newElem = new vector <int>(2);
				(*newElem)[0] = D[nbr_index];
				(*newElem)[1] = nbr_index;

				heap_insert ( newElem, Q );
			}
		}
		heap_remove ( Q );	
	}
	return D[end];
}