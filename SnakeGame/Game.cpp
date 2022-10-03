#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool isGameOver = false;

const int WIDTH = 50;
const int HEIGHT = 20;

int x, y, fruitX, fruitY, score, tailX[100], tailY[100], nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setUp()
{
    isGameOver = false;

    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    fruitX = rand() % WIDTH; // random number between 0 and WIDTH
    fruitY = rand() % HEIGHT; // random number between 0 and HEIGHT

    score = 0;
}

void draw()
{
    system("cls"); // clear the screen

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "G";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void input()
{
    if (_kbhit()) // if a key is pressed
    {
        switch (_getch()) // get the key pressed
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
    //    isGameOver = true;
    
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;

    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            isGameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main()
{
    setUp();
    while (!isGameOver)
    {
        draw();
        input();
        logic();
        Sleep(50); // sleep for 50 milliseconds
    } 
    return 0;
}