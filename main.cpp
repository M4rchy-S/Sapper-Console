#include <iostream>
#include <string>
#include <ctime>

#include <list>

#ifdef _WIN32
#include <windows.h>
#include "conio.h"
#endif

#ifdef linux
#include <unistd.h>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <cstring>
//  sudo apt-get install libncurses5-dev libncursesw5-dev
#endif


//#define DEBUG

using namespace std;


//          Main Data

int LENGTH;         
int WIDTH;          
int MINES;          
int WIN_POINTS;     


bool RUNNING = true;

struct coordinates
{
    int X;
    int Y;
};



list<coordinates> mines;
list<coordinates> zeroes;

int player_x = 0;
int player_y = 0;


char **bytemap;

//      Start Game Functions


//        Game Functions
void Print(bool);
void Game(int, int, int);
void Control();
void Update();
void GameOver(int code);

//      Support Functions
bool isBomb(int , int);
int getMinesCount3x3(int X, int Y);
void addElement(list<coordinates> &lst, coordinates coord);




int main()
{
    Game(3, 5, 5);

    
}

void Game(int mc, int length, int width)
{
    #ifdef linux
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    #endif
    //  Set Constants

    LENGTH      = length;
    WIDTH       = width;
    MINES       = mc;
    WIN_POINTS  = LENGTH*WIDTH - MINES;

    mines.clear();
    zeroes.clear();

    //      Generate Map
    bytemap = new char*[WIDTH];
    for(int i = 0 ; i < WIDTH; i++)
        bytemap[i] = new char[LENGTH];

    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < LENGTH; j++)
        {
            bytemap[i][j] = '+';
        }
    }


    // Generate mines position
    srand(time(0));
    for(int i = 0; i < MINES; i++)
    {
        int x = rand() % LENGTH;
        int y = rand() % WIDTH;
        if(isBomb(x, y))
        {
            i--;
            continue;
        }
        mines.push_back({x, y});
    }
   

    #ifdef DEBUG

    for(auto it = mines.begin(); it != mines.end(); it++)
       bytemap[it->Y][it->X] = '*';
    

    #endif


    //      Main Loop
    while(true)
    {
        Update();
        Print(true);
        Control();


        #ifdef _WIN32
        Sleep(210);
        system("cls");
        #endif
        #ifdef linux
        
        std::this_thread::sleep_for(std::chrono::milliseconds(210));
        //system("clear");
        //refresh();
        clear();

        #endif

        if(RUNNING == false)    
            break;
    }
    //      Remove dynamic data

    for(int i = 0 ; i < WIDTH; i++)
        delete[] bytemap[i];

    delete[] bytemap;

    //          Exit
    #ifdef _WIN32
    cout << "Bye!" << endl;
    cout << "Exiting from program..." << endl;
    exit(0);
    #endif

    #ifdef linux
    endwin();
    addstr("Bye!");
    addstr( "Exiting from program...");
    exit(0);
    #endif

}


void Control()
{
    #ifdef _WIN32
    if(kbhit())
    {
    #endif
        int ch = getch();
        // #ifdef linux
        // if(ch == ERR)
        //     return;
        // #endif

        switch(ch)
        {
        
            //      W       
            case 119: player_y--;
                    break;
            case 87: player_y--;
                break;
            //      A
            case 97: player_x--;
                    break;
            case 65: player_x--;
                break;
            //      D
            case 68: player_x++;
                    break;
            case 100: player_x++;
                break;
            //      S
            case 115: player_y++;
                    break;
            case 83: player_y++;
                break;
            //      Space
            case 32:
                    //       Main Logic Check
                    
                    if(isBomb(player_x, player_y))
                        GameOver(0);
                    else if(bytemap[player_y][player_x] != ' ')
                    {
                        int mines = getMinesCount3x3(player_x, player_y);
                        if(mines == 0) 
                        {
                            bytemap[player_y][player_x] = ' ';
                            zeroes.push_back({player_x, player_y});
                            for(auto it = zeroes.begin(); it != zeroes.end(); it++)
                            {
                                int X = it->X;
                                int Y = it->Y;
                                for(int k = Y - 1; k < Y + 2; k++)
                                    for(int p = X - 1; p < X + 2; p++)
                                    {
                                        if(k < 0 || k > WIDTH-1 || p < 0 || p > LENGTH-1)
                                            continue;

                                        mines = getMinesCount3x3(p, k);

                                        if( mines == 0)
                                        {
                                            bytemap[k][p] = ' ';
                                            addElement(zeroes, {p, k});
                                        }
                                        else
                                            bytemap[k][p] = char(mines+48);
                                            
                                        
                                    }

                            }
                            zeroes.clear();

                        }
                        else 
                            bytemap[player_y][player_x] = char(mines+48);
  
                        
                            
                    }


                    //  -------------------------
                    break;
            //      EXIT
            case 3: RUNNING = false;
                    break;
            case 27: RUNNING = false;
                    break;
        }

        if(player_x < 0) player_x = LENGTH-1;
        if(player_y < 0) player_y = WIDTH-1;

        if(player_x > LENGTH-1) player_x = 0;
        if(player_y > WIDTH-1) player_y = 0;
    
    #ifdef _WIN32
    }
    #endif
}


void Print(bool Cursor=true)
{
    #ifdef _WIN32

    static bool print_X = false; 
    cout << "  ";
    for(int i = 0; i < player_x; i++)
        cout << "   ";
    
    cout << "v" << endl;

    for(int i = 0; i < WIDTH; i++)
        {
            if(player_y == i)
                cout << "> ";
            else
                cout <<  "  ";

            for(int j = 0; j < LENGTH; j++)
            {
                if(j == player_x && i == player_y && print_X == true && Cursor == true)
                    cout << "X" << "  ";
                else
                    cout << bytemap[i][j] << "  ";
            }
            cout << endl;
        }
    print_X = !print_X;

    #endif

    #ifdef linux

    static bool print_X = false; 
    printw("  ");
    for(int i = 0; i < player_x; i++)
        addstr("   ");
    
    printw("v\n");

    for(int i = 0; i < WIDTH; i++)
        {
            if(player_y == i)
                printw("> ");
            else
                printw("  ");

            for(int j = 0; j < LENGTH; j++)
            {
                if(j == player_x && i == player_y && print_X == true && Cursor == true)
                {
                    addch('X');
                    printw("  ");
                }
                else
                {
                    addch(bytemap[i][j]);
                    printw("  ");
                }
            }
            printw("\n");
        }
    print_X = !print_X;
    

    #endif

#ifdef DEBUG

cout << "P_X: " << player_x << " P_Y: " << player_y << endl;

#endif
    

}

void Update()
{
    int points = 0;
     for(int i = 0; i < WIDTH; i++)
        {
            for(int j = 0; j < LENGTH; j++)
            {
               if(bytemap[i][j] != '+' && !isBomb(j, i) && bytemap[i][j] != '*')
               {
                    points++;   
               }
            }
            
        }
    if(points >= WIN_POINTS)
        GameOver(1);

}

void GameOver(int code)
{
    #ifdef _WIN32
    system("cls");
    

    cout << "\t-= Game Over =-" << endl;

    if(code == 0)
        cout << "\tYou lost" << endl;
    else if(code == 1)
        cout << "\tYou Won!" << endl;

    for(auto it = mines.begin(); it != mines.end(); it++)
       bytemap[it->Y][it->X] = '*';

    
    Print(false);
    cout << "Press any key to play again or ESC to exit" << endl;
    int choice = getch();
    if( choice == 27 || choice == 3)
        {
            RUNNING = false;
            return;
        }

    //      Remove dynamic data

    for(int i = 0 ; i < WIDTH; i++)
        delete[] bytemap[i];

    delete[] bytemap;

    
    Game(MINES, LENGTH, WIDTH);

    #endif

    #ifdef linux

    clear();
    
    addstr("\t-= Game Over =-\n");

    if(code == 0)
        addstr("\tYou lost\n");
    else if(code == 1)
        addstr("\tYou Won!\n");

    for(auto it = mines.begin(); it != mines.end(); it++)
       bytemap[it->Y][it->X] = '*';

    
    Print(false);
    addstr("Press any Space to play again or ESC to exit");
    refresh();
    while(true)
    {
    
    
        int choice = getch();
        
        if( choice == 27 || choice == 3 )
            {
                RUNNING = false;
                return;
            }
        else if(choice == 32)
        {
            break;
        }
    }

    //      Remove dynamic data

    for(int i = 0 ; i < WIDTH; i++)
        delete[] bytemap[i];

    delete[] bytemap;

    
    Game(MINES, LENGTH, WIDTH);

    #endif

    
}

bool isBomb(int X, int Y)
{
    for(auto it = mines.begin(); it != mines.end(); it++)
    {
        if(it->X == X && it->Y == Y)
        {
            return true;
        }
    }
    return false;
}

int getMinesCount3x3(int X, int Y)
{
    int count = 0;
    for(int k = Y-1; k < Y+2;k++)
        for(int p = X - 1; p < X + 2; p++)
        {
            if(isBomb(p, k))
                count++;
        }
    return count;
}

void addElement(list<coordinates> &lst, coordinates coord)
{
    for(auto it = lst.begin(); it != lst.end(); it++)
    {
        if(it->X == coord.X && it->Y == coord.Y)
        {
            return;
        }
    }
    lst.push_back(coord);
}