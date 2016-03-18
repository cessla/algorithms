#include <stdio.h>
#include <vector>
//#include <fstream>

using namespace std;
 
int n, m, s, p; //n - liczba wierzcholków, m - liczba krawedzi, s - wierzcholek startowy, p - liczba testów

vector<vector<int> >E;
vector<int>D;
 
const int INF = (1 << 30); // nieskonczonosc
 
int main()
{
	//ifstream infile("in");		
	//ofstream outfile("out2");
	scanf("%d", &p);
	//infile >> p;		//wczytywanie liczby testów
	
	for ( int k = 0; k < p; k++) {
		m = 0;		// liczba wczytanych krawedzi
		s = 0;
		scanf("%d", &n); // wczytywanie ilosci wierzcholków
		//infile >> n;
		
		//wczytywanie opisu grafu
		for ( int u = 0; u < n; u++ ) 
		{
			for ( int v = 0; v < n; v++ )
			{ 
				// iterowanie po macierzy sasiedztwa wierzcholków u-v
				int waga;
 
				scanf("%d", &waga);		// wczytywanie wagi wierzcholków
				//infile >> waga;
				//cout << waga;
				if ( waga != 0 )
				{
					// dodanie krawedzi do wektora
					m++;
					E.resize(m);
					E[m-1].resize(3);
					E[m-1][0] = u;
					E[m-1][1] = v;
					E[m-1][2] = waga;
				}
			}
		}
 
		D.resize(n);
 
		for (int i = 0; i < n; i++)
		{
			D[i] = INF; //tablica odleglosci
		}
		D[s] = 0; // odleglosc od wierzcholka startowego

		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < m; j++) 
			{
				int u = E[j][0], v = E[j][1], waga = E[j][2];
				if (D[u]!=INF && D[u]+waga < D[v]) //sprawdzenie odleglosci do poprzedniego wierzcholka i odleglosci do aktualnego wierzcholka
				{
					D[v] = D[u]+waga;

				}
			}
			 //zapisywanie wyniku do wyjscia
			for (int i = 0; i < n; i++)
			{
				if (D[i] < INF)
				{
					printf("%d ", D[i]);
					//outfile << D[i] << " ";
				}
				else {
					printf("0 ");
					//outfile << "0 ";
				}
			}

			
			printf("\n");
			//outfile << endl;
		}
			printf("\n");
			//outfile << endl;
		
		//system("PAUSE");
	}

	//system("PAUSE");
	//infile.close();
	//outfile.close();
    return 0;
}
