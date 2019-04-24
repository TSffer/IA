#include <string>
#include <utility> 
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

//NUM CROMOSOMAS->es el tamaño de la poblacion
//N_Nodes-> es el numero de ciudades que deben recorrerse

const int Num_Cromosomas = 10, N_Nodes = 20;

class TSP
{
	private:
		double crProb, MutationProb;
		int * MejorCromosoma;
		int (* Poblacion)[N_Nodes];
		int (* Nueva_Poblacion)[N_Nodes];

	public:
		vector<pair<double,double>> nodes;
		vector<int> recorrido;
		int check;
		int corrections = 0;
		TSP():Poblacion(new int[Num_Cromosomas][N_Nodes]), Nueva_Poblacion(new int[Num_Cromosomas][N_Nodes]),nodes(N_Nodes)
		{
			this->crProb = 0.9;
			this->MutationProb = 0.02;
			srand(time(NULL));
			check = 0;
			for(int i = 0; i < N_Nodes; i++)
			{
				nodes[i].first = ((double)rand() * 100) / (double)RAND_MAX;
				nodes[i].second = ((double)rand() * 100) / (double)RAND_MAX;
			}
			//GENERACION DE LA POBLACION INICIAL
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				//Random(Poblacion[i]);
				for(int j = 0; j < N_Nodes; j++)
				{
					Poblacion[i][j] = j;
				}

				for(int k = N_Nodes-1; k > 0; k--)
				{
					int random = (int)Random(k);
					int temp = Poblacion[i][k];
					Poblacion[i][k] = Poblacion[i][random];
					Poblacion[i][random] = temp;
				}
			}
		}

		void Mejor_Recorrido()
		{
			for(int i = 0; i < N_Nodes; i++)
			{
				this->recorrido.push_back(MejorCromosoma[i]);
			}
			return;
		}

		void SigGeneracion()
		{
			double Pesos_Rutas[Num_Cromosomas];

			for(int i = 0; i < Num_Cromosomas; i++)
			{
				Pesos_Rutas[i] = (1/Distancia_Recorrida(Poblacion[i]));///GT
			}
			check++;
			int Index1 = 0, Index2 = 0;

			Index1 = max_element(Pesos_Rutas, Pesos_Rutas + Num_Cromosomas) - Pesos_Rutas;
			this->MejorCromosoma = Poblacion[Index1];

			double HFits = 0;
			
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				if((i != Index1) and (Pesos_Rutas[i] > HFits))
				{
					HFits = Pesos_Rutas[i];
					Index2 = i;
				}
			}

			int Count = 0;

			//COPY NUEVAPOBLACION
			for(int i = 0; i < N_Nodes; i++)
			{
				Nueva_Poblacion[Count][i] = Poblacion[Index1][i];
			}
			Count++;
			//copyToNueva_Poblacion
			for(int i = 0; i < N_Nodes; i++)
			{
				Nueva_Poblacion[Count][i] = Poblacion[Index2][i];
			}
			Count++;

			while(1) //ADD
			{
				int * father;
				int * mother;
				father = Selection(Pesos_Rutas);
				mother = Selection(Pesos_Rutas);
				while (mother == father)
				{
					mother = Selection(Pesos_Rutas);
				}

				int ChilA[N_Nodes];
				int ChilB[N_Nodes];
				crossover(father, mother, ChilA, ChilB);
				Mutar_Cromosoma(ChilA);
				Mutar_Cromosoma(ChilB);
				
				if(!Duplicado_Cromosoma(ChilA, Count))
				{
					for(int i = 0; i < N_Nodes; i++)
					{
						Nueva_Poblacion[Count][i] = ChilA[i];
					}
					
					Count++;
				}
				
				if(Count == Num_Cromosomas)
				{
					break;
				}

				if(!Duplicado_Cromosoma(ChilB, Count))
				{
					for(int i = 0; i < N_Nodes; i++)
					{
						Nueva_Poblacion[Count][i] = ChilB[i];
					}				
					Count++;
				}

				if(Count == Num_Cromosomas)
				{
					break;
				}
			}

			for(int i = 0; i < Num_Cromosomas; i++)
			{
				memcpy(Poblacion[i], Nueva_Poblacion[i],sizeof(int) * N_Nodes);
			}
		}

		double Distancia_Euclidiana(int a,int b)
		{
		    return sqrt(pow(this->nodes[b].first - this->nodes[a].first,2) + pow(this->nodes[b].second - this->nodes[a].second,2));
		}

		double Distancia_Recorrida(int *cromosoma) 
		{
			double distance = 0.0;
	
			for(int i = 0; i < N_Nodes-1; i++)
			{
				distance = distance + Distancia_Euclidiana(cromosoma[i],cromosoma[i+1]);//sqrt((pow(dx, 2.0) + pow(dy, 2.0)));
			}

			distance = distance + Distancia_Euclidiana(cromosoma[N_Nodes-1],cromosoma[0]);

			return distance;
		}

		static double Random(double M)
		{
			return ((double)rand() * M) / (double)RAND_MAX;
		}

		int * Selection(double * P_rutas) const
		{
			double sum = 0;
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				sum = sum + P_rutas[i];
			}
			
			double random = Random(sum);

			sum = 0;
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				sum = sum + P_rutas[i];
				if(sum >= random)
				{
					return Poblacion[i];
				}
			}
			return(NULL);
		}
		
		void Mutar_Cromosoma(int *Cromosoma)
		{
			double random = Random(1);
			if(random > MutationProb)
			{
				return;
			}			

			int tmp;
			int random1 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));//(int)random
			int random2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			while(random1 == random2)
			{
				random2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			}

			tmp = Cromosoma[random1];
			Cromosoma[random1] = Cromosoma[random2];
			Cromosoma[random2] = tmp;
		}
		
		void crossover(int * father, int * mother, int * ChilA, int * ChilB)
		{
			double random = Random(1);
			if(random > crProb)
			{
				memcpy(ChilA,father,sizeof(int) * N_Nodes); 
				memcpy(ChilB, mother, sizeof(int) * N_Nodes);
				return;
			}

			int C_Index1 = (int)Random(N_Nodes);
			int C_Index2 = (int)Random(N_Nodes);

			while(C_Index2 == C_Index1)
			{
				C_Index2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			}

			int start;
			int end;
			if(C_Index1 < C_Index2)
			{
				start = C_Index1;
				end = C_Index2;
			}
			else
			{
				start = C_Index2;
				end = C_Index1;
			}
			
			memcpy(ChilA,father,sizeof(int)*N_Nodes);
			memcpy(ChilB,mother,sizeof(int)*N_Nodes);

			memcpy(ChilA + start,mother + start,sizeof(int)*(end - start));
			memcpy(ChilB + start,father + start,sizeof(int)*(end - start));		

			for(int i = 0; i < N_Nodes; i++)
			{

				if((i  >= start) and (i  < end)) 
				{
				}
				else
				{
					
					for(int j = start; j < end; j++)
					{
						if(ChilA[i] == ChilA[j])
						{
							ChilA[i] = -1;
						}
						if(ChilB[i] == ChilB[j])
						{
							ChilB[i] = -1;
						}
					}
				}
			}

			for(int i = 0; i < N_Nodes; i++)
			{
				if(ChilA[i] == -1)
				{
					//repair
					for(int j = 0; j < N_Nodes; j++)
					{
						int * missing = find(ChilA, ChilA + N_Nodes, ChilB[j]);

						if(missing == (ChilA + N_Nodes))
						{
							ChilA[i] = ChilB[j];
							break;
						}
					}
				}

				if(ChilB[i] == -1)
				{
					//repair
					for(int j = 0; j < N_Nodes; j++)
					{
						int * missing = find(ChilB, ChilB + N_Nodes, ChilA[j]);

						if(missing == (ChilB + N_Nodes))
						{
							ChilB[i] = ChilA[j];
							break;
						}
					}
				}
			}

		}
		
		bool Duplicado_Cromosoma(int *cromosoma, int populationCount)  // evita la existencia de cromosomas identicos
		{
			for(int i = 0; i < populationCount; i++)
			{
				if(check < populationCount)
				{
					corrections = check;
				}
				else
				{
					corrections = populationCount;
				}

				int Count = 0;
				for(int j = 0; j < N_Nodes; j++)
				{
					if(cromosoma[j] != Nueva_Poblacion[i][j])
					{
						break;
					}
					Count++;
				}

				if(Count == N_Nodes)
				{
					return true;
				}
			}
			return false;
		}

		void start(int iter)
		{
			int  num_generation = 0;
			double val = -1;
			while(num_generation < iter)
			{
				SigGeneracion();
				double newP = (1/Distancia_Recorrida(MejorCromosoma));
				if(newP > val)
				{
					val = newP;
					num_generation = 0;
					cout << ": " << (Distancia_Recorrida(MejorCromosoma)) << endl;
				}
				else
				{
					num_generation++;
				}
			}

			cout<<endl;
			cout << "Distancia: " << Distancia_Recorrida(MejorCromosoma) << endl;
			Mejor_Recorrido();
		}
};