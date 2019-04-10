#include <iostream>
#include <vector>
using namespace std;
#define INF 999999

class Nodo
{
    public:
        vector<Nodo *> childrens;
        int level;
        int id_player;
        int **table_state;

        Nodo(int **m_Estado,int n,int id_player)
        {
            this->table_state = m_Estado;
            this->level = n;
            this->id_player = id_player;
        }


        bool move_right(int y,int x,int **&tbl)
        {
            if((x+1 < 8) and (inside_Y(vertical_advance(y,1))) and (this->table_state[vertical_advance(y,1)][x+1] == 0))
            {
                tbl[y][x] = 0;
                tbl[vertical_advance(y,1)][x+1] = this->id_player;
                return true;
            }
            return false;
        }

        bool move_left(int  y,int x,int **&tbl)
        {
            if((x-1 >= 0) and (inside_Y(vertical_advance(y,1))) and (this->table_state[vertical_advance(y,1)][x-1]==0))
            {
                tbl[y][x] = 0;
                tbl[vertical_advance(y,1)][x-1] = this->id_player;
                return true;
            }
            return false;
        }

        bool eat_right(int y,int x,int **&tbl)
        {
            if((inside_Y(vertical_advance(y,2))) and (x+2 < 8) and (this->table_state[vertical_advance(y,1)][x+1] !=0) and (this->table_state[vertical_advance(y,1)][x+1] != id_player) and (this->table_state[vertical_advance(y,2)][x+2] == 0))
            {
                tbl[y][x] = 0;
                tbl[vertical_advance(y,1)][x+1] = 0;
                tbl[vertical_advance(y,2)][x+2] = this->id_player;
                return true;
            }
            return false;
        }

        bool eat_left(int y,int x,int **&new_table)
        {
            if((inside_Y(vertical_advance(y,2))) and (x-2 >= 0) and (this->table_state[vertical_advance(y,1)][x-1] != 0) and (this->table_state[vertical_advance(y,1)][x-1] != id_player) and (this->table_state[vertical_advance(y,2)][x-2] == 0))
            {
                new_table[y][x] = 0;
                new_table[vertical_advance(y,1)][x-1] = 0;
                new_table[vertical_advance(y,2)][x-2] = this->id_player;
                return true;
            }
            return false;
        }


        int vertical_advance(int y_h,int pos_desp)
        {
            int resp = 0;
            if(this->id_player == 1)
            {
                resp = y_h + pos_desp;
                return resp;
            }
            else
            {
                resp = y_h - pos_desp;
                return resp;
            }
        }

        bool inside_Y(int y_h)
        {
            if(this->id_player == 1)
            {
                if(y_h < 8)
                    return true;
                else
                    return false;
                
            }
            else               
            {
                if(y_h >= 0)
                    return true;
                else 
                    return false;
            }
        }

        int **get_tablero_estado()
        {
            return this->table_state;
        }

};


class Tree_Game
{
    public:
        int nivel_max;
        int id_IA;
        Nodo *m_head;

        Tree_Game(int **initial_state,int n,int var_ia)
        {
            this->nivel_max = n;
            this->id_IA = var_ia;
            this->m_head = new Nodo(initial_state,1,this->id_IA);
            Child(m_head);
        }

        void Descendants_level(Nodo *aux)
        {
            if((aux->level == this->nivel_max)) 
            {
                return;
            }
            
            for(int i=0;i<aux->childrens.size();i++)
            {
                Child(aux->childrens[i]);
                Descendants_level(aux->childrens[i]);
            }
        }

        void Child(Nodo *aux)
        {
            Nodo *n_aux;
            int **temp_tble;
            bool eat;

            for(int i = 0;i<8;i++)
            {    for(int j=0;j<8;j++)
                {
                    if(aux->table_state[i][j] == aux->id_player)
                    {
                        eat = false;
                        temp_tble = Copy(aux->table_state);
                        if(aux->eat_right(i,j,temp_tble))
                        {
                            int py;
                            if(aux->id_player == 1)
                                py = 2;
                            else
                                py = 1;

                            n_aux = new Nodo(temp_tble,aux->level+1,py);
                            aux->childrens.push_back(n_aux);
                            eat = true;
                        }

                        temp_tble = Copy(aux->table_state);
                        if(aux->eat_left(i,j,temp_tble))
                        {    
                            int py;
                            if(aux->id_player == 1)
                                py = 2;
                            else
                                py = 1;

                            n_aux = new Nodo(temp_tble,aux->level+1,py);
                            aux->childrens.push_back(n_aux);
                            eat = true;
                        }

                        if(eat) continue;

                        temp_tble = Copy(aux->table_state);
                        if(aux->move_right(i,j,temp_tble))
                        {
                            int py;
                            if(aux->id_player == 1)
                                py = 2;
                            else
                                py = 1;

                            n_aux = new Nodo(temp_tble,aux->level+1,py);
                            aux->childrens.push_back(n_aux);
                        }

                        temp_tble = Copy(aux->table_state);
                        if(aux->move_left(i,j,temp_tble))
                        {
                            int py;
                            if(aux->id_player == 1)
                                py = 2;
                            else
                                py = 1;
                                
                            n_aux = new Nodo(temp_tble,aux->level+1,py);
                            aux->childrens.push_back(n_aux);
                        }
                    }
                }
            }
        }

        int **Copy(int  **table)
        {
            int **A;
            A = new int *[8];
            for(int i=0;i<8;i++)
                A[i] = new int[8];

            for(int i = 0;i < 8;i++)
            {
                for(int j = 0;j < 8;j++)
                {
                    A[i][j] = table[i][j];
                }
            }
            return A;
        }

        int Peso(Nodo *p)
        {
            int fic_table1 = 0;
            int fic_table2 = 0;

            for(int i = 0; i < 8;i++)
            {
                for(int j = 0; j < 8;j++)
                {
                    //if(p->table_state[i][j] == p->id_player)
                    if(p->table_state[i][j] == 1)
                    {
                        fic_table1++;
                    }
                    //else if(p->table_state[i][j] != 0)
                    else if(p->table_state[i][j] == 2)
                    {
                        fic_table2++;
                    }
                }
            }
            //cout<<"Player 1: "<<fic_player1<<"Player 2: "<<fic_player2<<endl;
            //cout<<"DIF: "<< fic_player1 - fic_player2<<endl;
            return fic_table1 - fic_table2;
        }

        
        Nodo* MinMax(Nodo *estado)
        {
            Nodo* mejor_mov;
            double max,max_actual;
            max = -INF;

            for(int i=0;i < estado->childrens.size();i++)
            {
                max_actual = Peso(estado->childrens[i]);
                if(max_actual > max)
                {
                    max = max_actual;
                    mejor_mov = estado->childrens[i];
                }
            }
            return mejor_mov;
        }
        

       Nodo *minMax()
       {

           int value = Operation(this->m_head);
           for(int i=0;i < this->m_head->childrens.size();i++)
           {
                if(Peso(this->m_head->childrens[i]) == value)
                {
                    return this->m_head->childrens[i];
                }
           }
       }

       int Operation(Nodo *r,bool minmax = true)
       {
           int bestValue;
           if(r->childrens.size()==0)
           {
               bestValue = Peso(r);
           }        
           else if(minmax)
           {
               bestValue = -INF;
               for(int i=0;i < r->childrens.size();i++)
               {
                   int value = Operation(r->childrens[i],false);
                   bestValue = max(bestValue,value);
               }
           }
           else
           {
               bestValue = INF;
               for(int i=0; i < r->childrens.size();i++)
               {
                   int value = Operation(r->childrens[i],true);
                   bestValue = min(bestValue,value);
               }
           }
           return bestValue;      
       }

        virtual ~Tree_Game()
       {
           delete this->m_head;
           this->m_head = nullptr;
       }
};  
