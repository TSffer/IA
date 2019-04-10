#include "Player.cpp"
#include "TreeGame.cpp"
#include "Tablero.cpp"
#include <iostream>
#include <stdlib.h>

#define NUM_JUG 5
#define PLAYER 2
#define PLAYERIA 1

int **tablero;
class Game
{
    private:

    public:
        Tablero t;
        Game()
        {
            tablero = t.create_Table();
        }
        
        void Play()
        {
            Tree_Game *ia;
            int x1,x2,y1,y2;
            bool turno;

            Player player_1(PLAYER);
            
            if(PLAYER == 1)
                turno = true;
            else
                turno = false;
            
            while(End_of_game())
            {      
                t.mostrar_Tablero(tablero);          
                if(turno)
                {
                    cout<<endl;
                    
                    cout<<"DE: ";
                    cin>>x1 >> y1;
                    cout<<"HACIA: ";
                    cin>>x2 >> y2;
                    
                    //jugador1.calcular_mov(tablero,x1,y1);
                    while(!player_1.play(tablero,y1,x1,y2,x2))
                    {
                        cout<<"COORDENADAS INCORRECTAS!"<<endl;
                        cout<<"DE: ";
                        cin>>x1 >> y1;
                        cout<<"HACIA: ";
                        cin>>x2 >> y2;
                        
                    }
                    turno = false;
                }
                else
                {
                    ia = new Tree_Game(ia->Copy(tablero),NUM_JUG,PLAYERIA);
                    ia->Descendants_level(ia->m_head);

                    //int best_value = (ia->m_head)

                    copiar(ia->minMax()->table_state);
                    delete ia;
                    turno = true;
                }
            }
        }

        bool End_of_game()
        {
            bool p1 = 0;
            bool p2 = 0;
            int n_fichas1 = 0;
            int n_fichas2 = 0;

            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(tablero[i][j] == 1)
                    {
                        p1 = true;
                        n_fichas1++;
                    } 
                       
                    if(tablero[i][j] == 2)
                    {
                        p2 = true;
                        n_fichas2++;
                    }
                }
            }
            Player tmp(PLAYER);
            if((!p1) or (!tmp.move(tablero,PLAYERIA))) 
            {
                cout<<"Fichas 2 ha ganano"<<endl;
                return false;
            }

            if((!p2) or (!tmp.move(tablero,PLAYER)))
            {
                cout<<"Fichas 1 ha ganado"<<endl;
                return false;
            }
            return true;
        }        
        
        void copiar(int **a_copiar)
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    tablero[i][j] = a_copiar[i][j];
                }
            }
        }
};