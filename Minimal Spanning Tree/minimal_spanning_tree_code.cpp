#include <vector>
#include <stdio.h>
#include <set>

using namespace std;


vector <set <pair <int, int> > > E;	//tutaj trzymamy nasz graf
vector <bool> D;
vector <pair<int,pair<int,int> > > queue;		// kolejka priorytetowa
vector <int> scores;

int heap_size;
void min_heap_fix ( int, vector <vector <int> >&  );
void heap_remove ( vector <pair <int, pair<int, int> > >& );
void heap_insert (pair <int, pair<int,int> > , vector <pair <int, pair<int, int> > >&  );
void addNbrs (int v, vector <set <pair <int, int> > >& , vector <pair <int, pair<int,int> > >& );

int main()
{
	
	int t, n, m, w, sum, visited;			// t -liczba testów, n - liczba wierzcholków, m - liczba krawedzi, w - waga krawedzi, sum - suma wag krawedzi, visited - liczba wierzcholków do odwiedzenia

	scanf("%d", &t);		// wczytanie liczby testów

	for ( int k = 0; k < t; k++)
	{
		scanf("%*[\n]n=%d,m=%d", &n, &m);		

		D.resize(0);
		D.resize(n, false);
		//E.resize(0);
		E.resize(n);
		queue.resize(0);
		int v,u;
		visited = n;

		scanf("%*[\n]");
		for ( int i = 0; i < m; i++ )
		{
			scanf("{%d,%d}%d%*[ ]", &v, &u, &w);

			E[v].insert( pair<int,int> (u,w) );
			E[u].insert( pair<int,int> (v,w) );
		} 
		
		sum = 0;
		v = 0;
		D[v] = true;
		visited -= 1;
		addNbrs( v, E, queue);

		while ( visited > 0 )
		{		
			pair<int, pair<int, int> > x = queue[0];
			
			int v = x.second.first;
			int u = x.second.second;
			int w = x.first;
			int c;

			if ( D[v] == true )
			{	
				if ( D[u] == true )
				{
					heap_remove( queue );
					continue;
				} 
				else
				{
					c = u;
				}
			} 
			else
			{
				c = v;
			}

			D[c] = true;
			visited -= 1;
			sum += w;
			heap_remove( queue );
			addNbrs( c, E, queue);
		}
		//printf("%d\n", sum);
		scores.push_back(sum);
	}
	
	for ( std::vector <int>::iterator it = scores.begin(); it != scores.end(); ++it )
	{
		printf("%d\n", *it);
	}
	
	//system("PAUSE");
	return 0;
}


// funkcja do budowy  i naprawiania kopca minimalizujacego
void min_heap_fix ( int i, vector <pair <int, pair <int, int> > >& queue )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int min;
	pair <int, pair <int,int> >temp;

	if ( left <= heap_size && queue[left].first < queue[i].first )
	{
		min = left;
	}
	else
	{
		min = i;
	}

	if ( right <= heap_size && queue[right].first < queue[min].first )
	{
		min = right;
	}

	if ( min != i )
	{
		temp = queue[i];
		queue[i] = queue[min];
		queue[min] = temp;			//?? czy usuwac *t?
		min_heap_fix ( min, queue );
	}
}

 

//usuwanie min z kolejki i naprawa wlasnosci kopca
void heap_remove ( vector <pair <int, pair <int,int> > >& queue )
{
	pair <int, pair<int, int> > temp;
	if ( heap_size > 0 )
	{
		temp = queue[0];
		queue[0] = queue[heap_size-1];
		//delete temp; // usuwanie niepotrzebnego elementu typu struct queue
		heap_size -= 1;
		min_heap_fix ( 0, queue );
	}
}

// wstawianie do kolejki i naprawa kopca
void heap_insert (pair <int, pair <int,int> > elem, vector <pair <int, pair<int,int> > >& queue )
{
	heap_size += 1;
	int i = heap_size-1;
	queue.resize(heap_size);

	while ( i > 0 && elem.first < queue[(i-1)/2].first  )
	{
		queue[i] = queue[(i-1)/2] ;
		i = ( i-1 )/2;
	}
	
	queue[i] = elem;
}

void addNbrs (int c, vector <set <pair <int, int> > >& E, vector <pair <int, pair<int,int> > >& queue)
{
	for(std::set<pair <int,int> >::iterator it = E[c].begin(); it != E[c].end(); ++it) 
		{	
			int v = c;
			int u = (*it).first;
			int w = (*it).second;
			pair<int,int> edge = std::make_pair( v, u );
			pair <int, pair <int,int> > cost = std::make_pair( w, edge );
			heap_insert( cost, queue);	
			//E[v].erase( pair<int,int> (u,w) );
			E[u].erase( pair<int,int> (v,w) );
		}
	E[c].clear();
}