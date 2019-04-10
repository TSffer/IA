#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class Tablero
{
    private:
        int **tablero;
    public:
        //char tablero[8][8];
        string blancas = "░";
        string negras  = "█";

        Tablero(){};

        int ** create_Table()
        {
            tablero = new int*[8];
            for(int i=0;i<8;i++)
            {
                tablero[i] = new int[8];
            }

            for(int i = 0;i < 8;i++)
            {
                for(int j = 0;j < 8;j++)
                {
                    if((i <= 2) and ((i+j)%2 != 0))
                    {
                        tablero[i][j] = 1;
                    }
                    else if((i >= 5) and ((i+j)%2 !=0))
                    {
                        tablero[i][j] = 2;
                    }
                    else
                    {
                        tablero[i][j] = 0;
                    }
                    
                }
            }
            return tablero;
        }

        char ** transform_Tablero(int **tabla)
        {
            char **tablero_char;
            tablero_char = new char*[8];
            for(int i=0;i<8;i++)
            {
                tablero_char[i] = new char[8];
            }

            for(int i = 0;i < 8;i++)
            {
                for(int j = 0;j < 8;j++)
                {
                    if(tabla[i][j] == 1)
                    {
                        tablero_char[i][j] = 'O';
                    }
                    else if(tabla[i][j] == 2)
                    {
                        tablero_char[i][j] = 'X';
                    }
                    else if(tabla[i][j] == 0)
                    {
                        tablero_char[i][j] = ' ';
                    }
                    
                }
            }

            return tablero_char;
        }

        void mostrar_Tablero(int **tabla)
        {
            char **a = transform_Tablero(tabla);
            cout<<"\n "<<endl;

            for(int i = 0;i < 8; i++)
            { 
                cout<<"   "<<i<<" ";
            }
            cout<<endl;

            for(int i = 0;i < 8;i++)
            {
                cout<<i;
                for(int j = 0;j < 8;j++)
                {
                    if((a[i][j] == 'X' || a[i][j] == 'O' || a[i][j] == 'C' || a[i][j]=='D') and ((i+j)%2 != 0))
                    {
                        cout<<blancas<<blancas<<a[i][j]<<blancas<<blancas;
                    }
                    else if(a[i][j] == ' ' and ((i+j)%2==0))
                    {
                        cout<<negras<<negras<<negras<<negras<<negras;
                    }
                    
                    else if(a[i][j]==' ' and ((i+j)%2!=0))
                    {
                        cout<<blancas<<blancas<<blancas<<blancas<<blancas;
                    }
                }
                cout<<endl;
            }
            cout<<"\n"<<endl;
        }

        void modificar_Tablero(int i , int j , char c)
        {
            tablero[i][j] = c;
        }
};

