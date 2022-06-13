/*
PROJECT: SNAKE GAME
BY     : AKANKSHA KEJRIWAL
STARTED: 10th JUNE 2022
ENDED  : 12th JUNE 2022
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//==============================================================
//                         VARIABLES USED
//==============================================================
const int width=30 , height=20; 
const int x1=41 , y1=11 , x2=70 , y2=30;//coordinates of wall

int fruitX , fruitY;   
bool gameover;     
int headX , headY;   //Snake head
int tailX[101] , tailY[101];    //Snake tail coordinates
int nTail;  //Length of tail
int score;

enum Direction {STOP=0 , LEFT , UP , RIGHT , DOWN}; //Controls
Direction dir;

//==============================================================
//          FUNCTION FOR THE AXIS (GOTOXY)
//==============================================================
void gotoxy(int x , int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , coord);
}

//==============================================================
//                       GAME INSTRUCTIONS
//==============================================================
void instructions()
{
    cout << "\n\n\n\n\n\t\t\t";

    //Top Border
    cout << char(201);
    for (int i=1 ; i<=43 ; i++)
        cout << char(205);
    cout << char(187);

    //Instructions
    cout << "\n\t\t\t" << char(186) << "               INSTRUCTIONS                " << char(186);
    cout << "\n\t\t\t" << char(186) << " ";
    for (int i=1 ; i<=41 ; i++)
        cout << char(196);
    cout << " " << char(186);
    cout << "\n\t\t\t" << char(186) << "                                           " << char(186);
    cout << "\n\t\t\t" << char(186) << " YOUR GOAL IS TO COLLECT AS MANY FRUITS AS " << char(186);
    cout << "\n\t\t\t" << char(186) << "      POSSIBLE AND MAXIMISE THE SCORE.     " << char(186);
    cout << "\n\t\t\t" << char(186) << "                                           " << char(186);
    cout << "\n\t\t\t" << char(186) << "  TURN THE SNAKE USING KEYS A, S, D AND W  " << char(186);
    cout << "\n\t\t\t" << char(186) << "             A = TURN LEFT                 " << char(186);
    cout << "\n\t\t\t" << char(186) << "             W = TURN UP                   " << char(186);
    cout << "\n\t\t\t" << char(186) << "             D = TURN RIGHT                " << char(186);
    cout << "\n\t\t\t" << char(186) << "             S = TURN LEFT                 " << char(186);
    cout << "\n\t\t\t" << char(186) << "                                           " << char(186);
    cout << "\n\t\t\t" << char(186) << "         PRESS P TO PAUSE THE GAME         " << char(186);
    cout << "\n\t\t\t" << char(186) << "        THEN PRESS ANY KEY TO RESUME       " << char(186);
    cout << "\n\t\t\t" << char(186) << "                                           " << char(186);
    cout << "\n\t\t\t" << char(186) << "              PRESS X TO STOP              " << char(186);
    cout << "\n\t\t\t" << char(186) << "                                           " << char(186);
    cout << "\n\t\t\t";

    //Bottom border
    cout << char(200);
    for (int i=1 ; i<=43 ; i++)
        cout << char(205);
    cout << char(188);
    cout << "\n\t\t\t" << "           PRESS ANY KEY TO START:";
    getch();
}

//==============================================================
//            DRAW GAME BORDER AND INITIALIZE VARIABLES
//==============================================================
void setGame()
{
    //DRAW BORDER

    //Top wall
    gotoxy(40 , 10);
    cout << char(201);
    for (int i=1 ; i<=30 ; i++)
        cout << char(205);
    cout << char(187);

    //Left and right walls
    for (int i=11 ; i<=30 ; i++)
    {
        gotoxy(40 , i);
        cout << char(186);
        gotoxy(71 , i);
        cout << char(186);
    }

    //Bottom wall
    gotoxy(40 , 31);
    cout << char(200);
    for (int i=1 ; i<=30 ; i++)
        cout << char(205);
    cout << char(188);

    //After drawing the walls, the playable region is 
    //41 to 70 along x axis
    //11 to 30 along y axis

    //INITIALIZE VARIABLES
    srand(time(0));

    //Snake is set at center of box
    headX = (x1+x2)/2;
    headY = (y1+y2)/2;
    fruitX = x1 + (rand() % width);
    fruitY = y1 + (rand() % height);
    gameover = false;
    dir = RIGHT;    //Start game from right direction
    score = 0;
    nTail = 0;  //Initially length of tail is 0
    tailX[0] = tailY[0] = 0;
}

//==============================================================
//                        DRAW SNAKE
//==============================================================
void draw()
{
    gotoxy(0,0);
    gotoxy(49 , 33);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);    //Blue color
    cout << "SCORE : " << score;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);    //Red color for fruit
    gotoxy(fruitX,fruitY);
    cout << char(162);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);    //Green color for snake
    gotoxy(headX,headY);
    cout << char(233);
    gotoxy(tailX[0],tailY[0]);  //Previous head is now part of tail so change character at that position
    cout << "o";
    gotoxy(tailX[nTail],tailY[nTail]);  //As snake moves forward remove last position of tail
    cout << " ";    
    gotoxy(0,0);
}

//==============================================================
//                      INPUT FUNCTION
//==============================================================
void input()
{
    //Keys a , s , d , w are used for directions
    //     W
    //   A + D
    //     S

    //User presses x if he wants to stop
    
    if (_kbhit()) //If user pressed a key
    {
        switch (getch())
        {
            case 'a' : 
                if(dir!=RIGHT)  //Do not change the direction if user tries to go in opposite direction
                        dir = LEFT;
                break;

            case 'w' : 
                if(dir!=DOWN)
                        dir = UP;
                break;

            case 'd' : 
                if(dir!=LEFT)
                        dir = RIGHT;
                break;

            case 's' : 
                if(dir!=UP)
                        dir = DOWN;
                break;
            
            case 'x' : gameover = true;
                break;
            
            case 'p' : getch(); //Pause until another key is pressed
        }
    }
}

//==============================================================
//                      MOVE SNAKE
//==============================================================
void moveSnake()
{
    Sleep(150);//1.5 sec delay

    int i;
    //Shifting each position of tail forward by one 
    //where nTail index stores the coordinates of part of tail to be removed
    for(i=nTail ; i>0 ; i--)
    {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    tailX[0] = headX;
    tailY[0] = headY;

    switch (dir)
    {
        case LEFT : headX--;
            break;

        case RIGHT : headX++;
            break;

        case UP : headY--;
            break;

        case DOWN : headY++;
            break;
    }

    //Check boundary conditions
    //If snake reaches the boundary move it to other side
    if(headX > x2)
        headX = x1;
    else if(headX < x1)
        headX = x2;
    
    if(headY > y2)
        headY = y1;
    else if(headY < y1)
        headY = y2;

    //If head collides with body, game over
    for (int i=0 ; i<=nTail ; i++)
        if(headX==tailX[i] && headY==tailY[i])
        {
            gameover=true;
            return;
        }

    //If snake collects fruit
    if(headX==fruitX && headY==fruitY)
    {
        score += 10;
        nTail++;

        //Generate fruit in a free space
        int f=0;
        while(!f)
        {
            f=1;
            fruitX = x1 + (rand() % width);
            fruitY = y1 + (rand() % height);
            for (int i=0 ; i<nTail ; i++)
                if(fruitX==tailX[i] && fruitY==tailY[i])
                {
                    f=0;
                    break;
                }
        }
    }

}

//==============================================================
//                         MAIN FUNCTION
//==============================================================
main()
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);    //Blue color text
    instructions();
    
    system("cls");
    setGame();

    while(!gameover)
    {
        draw();
        input();
        moveSnake();
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);    //Blue color
    gotoxy(40,20);
    for (int i=1 ; i<=11 ; i++)
        cout << char(177);
    cout << "GAME OVER";
    for (int i=1 ; i<=12 ; i++)
        cout << char(177);

    return 0;
}
