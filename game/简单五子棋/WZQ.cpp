#include <iostream>
#include <string>
static char matrix[9][9];
char player = 'X';
static int n = 0;
static int x = 0;
static int y = 0;
void Draw()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void Input()
{    
    std::string t;
    while(1){   
    getline(std::cin,t);
    if(t=="w"){
        x --;
        if(x<0){    
            x=0;
        }
        if( matrix[x][y] != 'X' && matrix[x][y] != '#'){
        matrix[x][y] = '*';
        Draw();
        matrix[x][y] = '_';
        }
    }
    else if(t=="s"){
      x ++;
      if(x>9){
          x=9;
      }
    if (matrix[x][y] != 'X' & matrix[x][y] != '#'){
        matrix[x][y] = '*';
        Draw();
        matrix[x][y] = '_';
        }
    }   
    else if(t=="a"){
       y --;
       if(y<0){    
            y=0;
        }
        if( matrix[x][y] != 'X' && matrix[x][y] != '#'){
        matrix[x][y] = '*';
        Draw();
        matrix[x][y] = '_';
        }
    }
    else if(t=="d"){
        y  ++;
        if(y>9){
            y = 9;
        } 
        if( matrix[x][y] != 'X' && matrix[x][y] != '#'){
        matrix[x][y] = '*';
        Draw();
        matrix[x][y] = '_';
        }
    }
    else if(t =="j"){
        matrix[x][y] = player;
        break;
    }
    std::cout <<  player << " turn. ";
    }

}
void TogglePlayer()
{
    if (player == 'X')
        player = '#';
    else
        player = 'X';
    n++;
}
bool Win()
{
    for(int i = -1; i < 9; i++){
        for(int j = -1; j < 9; j++){
              if(matrix[i][j+1] == 'X' && matrix[i][j+2] =='X'&& matrix[i][j+3] == 'X' && matrix[i][j+4] =='X' && matrix[i][j+5]=='X'){
                       std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i+1][j] == 'X' && matrix[i+2][j] =='X'&& matrix[i+3][j] == 'X'&&matrix[i+4][j] =='X'&& matrix[i+5][j]=='X'){
                         std::cout <<  player << " wins ";
                return true;
                }
                
                if(matrix[i+9+1][j] =='X' && matrix[i+9*2+2][j] =='X' && matrix[i+9*3+3][j] =='X'&& matrix[i+9*4+4][j] =='X'&& matrix[i+9*5+5][j]=='X'){
                         std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i][j+9+1] =='X' && matrix[i][j+9*2+2] =='X' && matrix[i][j+9*3+3] =='X' && matrix[i][j+9*4+4] =='X'  &&matrix[i][j+9*5+5]=='X'){
                         std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i][j+1] == '#' && matrix[i][j+2] =='#'&& matrix[i][j+3] == '#' && matrix[i][j+4] =='#' && matrix[i][j+5]=='#'){
                         std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i+1][j] == '#' && matrix[i+2][j] =='#'&& matrix[i+3][j] == '#'&&matrix[i+4][j] =='#'&& matrix[i+5][j]=='#'){
                    
                      std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i+9+1][j] =='#' && matrix[i+9*2+2][j] =='#' && matrix[i+9*3+3][j] =='#'&& matrix[i+9*4+4][j] =='#'&& matrix[i+9*5+5][j]=='#'){
                      std::cout <<  player << " wins ";
                return true;
                }
                if(matrix[i][j+9+1] =='#' && matrix[i][j+9*2+2] =='#' && matrix[i][j+9*3+3] =='#' && matrix[i][j+9*4+4] =='#'  &&matrix[i][j+9*5+5]=='#'){
                      std::cout <<  player << " wins ";
                return true;
                }
            }
    }
    return false;
}
void inititalize(){
    std::cout<<"按w,s,a,d 中的一个（注意一个）然后*坐标点移动，按j选择确定把你的棋子下在那里。"<<std::endl;
      std::cout<<"按回车键确定移动方向"<<std::endl;
    for (int i = 0; i < 9; i++)
    {
    for (int j = 0; j < 9; j++)
        {
            matrix[i][j] = '_';
        }
    }
}
int main()
{
    inititalize();
    Draw();
    while (1)
    {
        Input();
        Draw();
        if(Win())
        {
            break;
        }
        TogglePlayer();
    }
    return 0;
}
