#include <iostream>

using namespace std;

class Player
{
    public:
        int player_H;
        Player(int pl)
        {
            player_H = pl;
        }

        bool move_right(int y,int x,int **table)
        {
            int new_y = vertical_advance(y,1);
            if((x+1 < 8) and (inside_Y(new_y)) and (table[new_y][x+1] == 0))
            {
                return true;
            }
            return false;
        }

        bool move_left(int y,int x,int **table)
        {
            int new_y = vertical_advance(y,1);
            if((x-1 >= 0) and (inside_Y(new_y)) and (table[new_y][x-1] == 0))
            {
                return true;
            }
            return false;
        }

        bool eat_left(int y,int x,int **table)
        {
            if((inside_Y(vertical_advance(y,2))) and (x-2 >= 0) and (table[vertical_advance(y,1)][x-1] != 0) and (table[vertical_advance(y,1)][x-1] != player_H))
            {
                return true;
            }
            return false;
        }

        bool eat_right(int y,int x,int **table)
        {
            if((inside_Y(vertical_advance(y,2))) and (x+2 < 8) and (table[vertical_advance(y,1)][x+1] != 0) and (table[vertical_advance(y,1)][x+1] != player_H))
            {
                return true;
            }
            return false;
        }

        int vertical_advance(int y,int sum_res)
        {
            int resp = 0;
            if(this->player_H == 1)
            {
                resp = y+sum_res;
                return resp;
            }
            else
            {
                resp = y-sum_res;
                return resp;
            }
            
           
        }

        bool inside_Y(int y)
        {
            if(player_H == 1)
            {
                if(y < 8)
                    return true;
                else
                    return false;
            }
            else
            {
                if(y >= 0)
                    return true;
                else
                    return false; 
            }
        }

        bool play(int **&table_state, int x_1,int y_1,int x_2,int y_2)
        {
            if((y_1 < 0) or (y_1 > 7) or (x_1 < 0)  or (x_1 > 7) or (y_2 < 0) or (y_2 > 7) or (x_2 < 0) or (x_2 > 7) )
            {
                return false;
            }
            
            if((x_2 - 2 == x_1) and (vertical_advance(y_1,2) == y_2) and (eat_right(y_1,x_1,table_state)))
            {
                table_state[y_1][x_1] = 0;
                table_state[vertical_advance(y_1,1)][x_1+1] = 0;
                table_state[y_2][x_1+2] = player_H;
                return true;
            }
            else if((x_2+2 == x_1) and (vertical_advance(y_1,2) == y_2) and (eat_left(y_1,x_1,table_state)))
            {
                table_state[y_1][x_1] = 0;
                table_state[vertical_advance(y_1,1)][x_1-1] = 0;
                table_state[y_2][x_2] = player_H;
                return true;
            }
            else if((x_2-1 == x_1) and (vertical_advance(y_1,1) == y_2) and (move_right(y_1,x_1,table_state)))
            {
                table_state[y_1][x_1] = 0;
                table_state[y_2][x_2] = player_H;
                return true;
            }
            else if((x_2+1 == x_1) and (vertical_advance(y_1,1) == y_2) and (move_left(y_1,x_1,table_state)))
            {
                table_state[y_1][x_1] = 0;
                table_state[y_2][x_2] = player_H;
                return true;
            }

            return false;
        }

        bool move(int **table_state,int id_player)
        {
            for(int i = 0;i < 8;i++)
            {
                for(int j = 0;j < 8;j++)
                {
                    if((table_state[i][j] == id_player)) 
                    {
    
                        if(eat_right(i,j,table_state))
                        {
                            return true;
                        }
                        else if(eat_left(i,j,table_state))
                        {
                            return  true;
                        }
                        else if(move_left(i,j,table_state))
                        {
                            return true;
                        }
                        else if(move_right(i,j,table_state))
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }


};