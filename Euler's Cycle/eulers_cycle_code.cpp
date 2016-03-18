#include <vector>
#include <stdio.h>
#include <stack>
#include <set>

using namespace std;


vector<vector<int> > ce;		//kontener na kolejne wierzcholki cyklu
stack<int> stos;	//stos tymczasowy
vector<int> temp;
vector<multiset<int> > E;//tutaj trzymamy nasz graf


int main()
{
	
	int t, n, m;			// t -liczba testów, n - liczba wierzcholków, m - liczba krawedzi
	
	scanf("%d", &t);		// wczytanie liczby testów
	ce.resize(t);

	for ( int k = 0; k < t; k++)
	{
		scanf("%*[\n]n=%d,m=%d", &n, &m);		
		//printf("%d %d %d", t, n, m);

		E.resize(n);
		int v,u;

		//scanf("%*[\n]{%d,%d}", &v, &u);

		//	E[v].insert(u);
		//	E[u].insert(v);
		scanf("%*[\n]");
		for ( int i = 0; i < m; i++ )
		{
			
		
			scanf("{%d,%d}%*[ ]", &v, &u);

			E[v].insert(u);
			E[u].insert(v);
		} 

		stos.push(0);
		while(stos.size() > 0)
		{
			int v=stos.top();
			int u;

			if ( E[v].size() != 0 )
			{
				u = *E[v].begin();
				// usuwam krawedz v-u
				E[v].erase(u);
				E[u].erase(v); 

				stos.push(u);    //wrzucam na stos
			}
			else	//jezeli wierzcholek nie ma juz krawedzi wychodzacych
			{
				stos.pop();
				ce[k].push_back(v);	// to wrzucam go do vectora
			}   
		}
	}

	for ( int k = 0; k < t; k++)
	{
		for ( int j = 0; j < ce[k].size(); j++)
		{
			printf("%d ", ce[k][j]);
		}
	printf("\n");
	}
	
	//system("PAUSE");
	return 0;
}
