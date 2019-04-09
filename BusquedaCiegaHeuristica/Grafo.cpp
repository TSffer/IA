#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <map>
#include <queue>
#include <cmath>
#include <unordered_map> 
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 

#define INF 10000000
using namespace std;

class cmp
{
    public:
        bool operator()(const pair<int,double> &a, const pair<int ,double> &b)   // Pair<id_nodo , peso_nodo>
        {
            return a.second > b.second;
        }
};
bool sortbysec(const pair<int,double> &a, const pair<int,double> &b) 
{ 
    return (a.second < b.second); 
} 
class  Edge
{
    public:
        int v,w;      // ID's  
        double c;     // peso
        Edge(int v = -1,int w = -1, double c= -1.0) 
        {
            this->v = v;
            this->w = w;
            this->c = c;
        }
};

class Nodo
{
    public:
        double coord_x , coord_y;
        int id_nodo, N_edge = 0;
        double distance;
        Nodo(){}
        Nodo(double x , double y)
        {
            this->coord_x = x;
            this->coord_y = y;
        }   

        Nodo(int id,double peso,double x,double y)
        {
            this->coord_x = x;
            this->coord_y = y;
            this->distance = peso;
            this->id_nodo = id;
        }   
};

class  Grafo
{
    private:
        int Vcnt , Ecnt;
        bool digraph;
        
     
    public:
        vector<bool> visitado;
        vector<int> recorrido;
        vector<Nodo> nodes;
        vector<map<int,double> > adj;
        vector< pair<double,double> > coordenadas;

        Grafo(int V,bool digraph = false):adj(V),coordenadas(V)
        {
            this->Vcnt = V;
            this->Ecnt = 0;
            this->digraph = digraph;
            this->visitado.assign(V,false);
        }

        int V() const
        {
            return Vcnt;
        }

        int E() const
        {
            return Ecnt;
        }

        bool directed() const
        {
            return digraph;
        }

        void insert_edge(Edge e)
        {
            if(directed())
                adj[e.v][e.w] = e.c;
            else
            {
                adj[e.v][e.w] = e.c;
                adj[e.w][e.v] = e.c;
            }
            Ecnt++;
        }

        int size()
        {
            return this->nodes.size();
        }

        void insert_nodo(Nodo n)
        {
            this->nodes.push_back(n);
        }

        void llenarCoordenadas(double x,double y,int n)
        {
            coordenadas[n].first = x;
            coordenadas[n].second = y;
        }

        double Distancia_Euclidiana(int a,int b)
        {
            return sqrt(pow(this->nodes[b].coord_x - this->nodes[a].coord_x,2) + pow(this->nodes[b].coord_y - this->nodes[a].coord_y,2));
        }


    void crear_nodos()
    {
        srand(time(NULL));
        for(int i=0; i<V();i++)
        {
            //insert_nodo(Nodo((double)rand()/(RAND_MAX),(double)rand()/(RAND_MAX)));
            insert_nodo(Nodo(rand()%100,rand()%100));
        }
        return;
    }

    vector<pair<int,double>> Nodos_cercanos(int id_Nodo,int N_rand)
    {
        vector<pair<int,double>> min; 
        //priority_queue<pair<int,double>,vector<pair<int,double>>,cmp> queue;
        vector< pair<int,double> > A;

        for(int i = 0; i < V() ;i++)
        {
            //queue.push({i,Distancia_Euclidiana(i,id_Nodo)});
            if(i == id_Nodo) continue;
            A.push_back(make_pair(i,Distancia_Euclidiana(i,id_Nodo)));
        }

        sort(A.begin(),A.end(),sortbysec);

        for(int i=0;i < N_rand;i++)
        {
            //min.push_back(queue.top());
            //queue.pop();
            min.push_back(A[i]);
        }
    
        /*for(int i=0;i<min.size();i++)
        {
            cout<<min[i].first<<" "<<min[i].second<<endl;
        }
        */
        return min;
    }

    void crear_edges()
    {
        int N_rand = 0;
        vector<pair<int,double>> cercanos;
        srand(time(NULL));
        
        for(int i = 0;i<V();i++)
        {
            N_rand = rand()%8+2;
            //cout<<N_rand<<endl;
            cercanos = Nodos_cercanos(i,N_rand);

            for(int j = 0;j < cercanos.size();j++)
            {
                if(this->nodes[i].N_edge < N_rand)
                {
                    insert_edge(Edge(i,cercanos[j].first,cercanos[j].second));
                    this->nodes[i].N_edge++;
                    this->nodes[j].N_edge++;
                }
            }
            cercanos.clear();
        }
       // cout<<"NUM E: "<<this->Ecnt<<endl;
    }

///////////////////////////////////////////////////////////////////////////
    static bool comparison(const Nodo a,const Nodo b)
    {
        return (a.distance < b.distance);
    }

    vector<Nodo> classifyANode(Nodo arr[],int n,int k,Nodo p)
    {
        for(int i=0;i<n;i++)
        {
            arr[i].distance = sqrt((arr[i].coord_x - p.coord_x) * (arr[i].coord_x - p.coord_x) + 
                                (arr[i].coord_y - p.coord_y) * (arr[i].coord_y - p.coord_y));
        }

        std::sort(arr,arr+n,comparison);

        int freq1 = 0;
        int freq2 = 0;
        vector<Nodo> A;
        for(int i=0;i<k;i++)
        {
           // A.push_back(Nodo);
        }
    }

    void A_star(int inicial,int destino)
    {
        int cont = 0;
        priority_queue<pair<int,double> , vector<pair<int,double>>,cmp> Q;
        vector<bool> vist(V(),false);

        vector<int> previo(V(),-1);
        vector<double> distancia(V(),INF);
        visitado.assign(V(),false);
        //scout<<" INF "<<INF<<endl;

        Q.push(make_pair(inicial,0.0));
        distancia[inicial] = 0.0;
        int actual,adyacente;
        double peso;

        while(!Q.empty())
        {
            actual = Q.top().first;
            Q.pop();
            if(vist[actual]) continue;

            vist[actual] = true;

            for(auto it = adj[actual].begin();it != adj[actual].end();it++)
            {
                adyacente = (*it).first;
                peso = (*it).second;

                if(!vist[adyacente])
                {
                    if(distancia[actual] + peso < distancia[adyacente])
                    {
                        ///cout<<"Entre"<<endl;
                        distancia[adyacente] = distancia[actual] + peso;
                        previo[adyacente] = actual;
                        Q.push(make_pair(adyacente,distancia[adyacente] + Distancia_Euclidiana(actual,destino)));
                    }
                }

                /*if((visitado[adyacente]) and (adyacente == destino))
                {
                    print1(destino,previo,cont);
                    cout<<endl;
                    //cout<<"#nodos"
                    return;
                }*/
            }
        }
        Ruta(destino,previo,cont);

    } 

    void Ruta(int destino,vector<int> &previo,int &cont)
    {
        if(previo[destino] != -1)
        {
            Ruta(previo[destino],previo,cont);
        }
        recorrido.push_back(destino);
        //cout<<destino<<endl;
        cont++;
    }

    ///////////////////////////////////////////////////////////////

    void busqueda_anchura(int s,int t)
    {
        queue<int> v;
        v.push(s);

        int tmp;

        map<int,double>::iterator it;
        while(!v.empty())
        {
            tmp = v.front();
            recorrido.push_back(tmp);
            if(tmp == t)
            {
                    return;
            }
            for(it = adj[tmp].begin();it != adj[tmp].end();it++)
            {
                if(!visitado[(*it).first])
                {
                    visitado[(*it).first] = true;
                    v.push((*it).first);
                }

            }
            v.pop();
        }
    }
/*
    void breadth_first_search(int start,int goal)
    {
        queue<int> frontier;
        frontier.push(start);

        unordered_set<int> visited;
        visited.insert(start); 

        while(!frontier.empty())
        {
            int current = frontier.front();
            frontier.pop();

            recorrido.push_back(current);
            if(current == goal)
            {
                break;
            }
            for(auto it = adj[current].begin();it != adj[current].end();it++)
            {
                if(visited.find((*it).first)  == visited.end())
                {
                    frontier.push((*it).first);
                    visited.insert((*it).first);
                }
            }
        }
        
        

    }
*/
};
