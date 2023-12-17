
// project.cpp
// This program will create a pong game.
// Author Hao Thai
// Last Edited: 12/7/21

#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;
// creates an enumeration for how the ball moves: vertical, horizontal, and no movement
enum eDir
{
    STOP = 0,
    LEFT = 1,
    UPLEFT = 2,
    DOWNLEFT = 3,
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};

// create a class for the ball
class cBall
{
private:
    // store the position of the ball
    int x, y;
    // store the position of the original X, Y coordinates
    int originalX, originalY;
    eDir direction;
    // create constructor to take the position of the ball x-y coordinates
public:
    cBall(int posX, int posY)
    {
        // takes the original points to reset the ball
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }
    // resets the ball to the original coordinate when a user scores a goal
    void Reset()
    {
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    // takes in a new direction for the ball
    void changeDirection(eDir d)
    {
        direction = d;
    }
    // changes the direction of the ball randomly
    void randomDirection()
    {
        // creates random numbers from 1 - 6
        direction = (eDir)((rand() % 6) + 1);
    }
    // replace the current position of the ball
    inline int getX() { return x; }
    inline int getY() { return y; }
    // returns the value of the direction
    inline eDir getDirection() { return direction; }

    // let the ball move using a reverse x and y coordinates graph
    // increse and descrease coordinates using increments
    void Move()
    {
        switch (direction)
        {
        // using UPLEFT, DOWNLEFT, UPRIGHT, and DOWNRIGHT will help the ball move at an angle instead of only horizontal and vertical movements
        // stops the ball from moving
        case STOP:
            break;

            // ball moves left
            // the x-coordinate will decrease
        case LEFT:
            x--;
            break;

            // ball moves right
            // the x-coordinate will increase
        case RIGHT:
            x++;
            break;

            // ball moves up to the left
            // the x coordinate will decrease and the y coordinate will increase
        case UPLEFT:
            x--;
            y--;
            break;

            // ball moves down to the left
            // the x-coordinate will decrease and the y-coordinate will increase
        case DOWNLEFT:
            x--;
            y++;
            break;

            // ball moves down to the left
            // the x-coordinate will increase and the y-coordinate will decrease
        case UPRIGHT:
            x++;
            y--;
            break;

            // ball moves down to the right
            // the x-coordinate will increase and the y-coordinate will increase
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
        }
    }
    // overloads operator and passes the function of an ball (object) then returns it
    friend ostream &operator<<(ostream &o, cBall c)
    {
        // output the direction of the ball abd shows x and y coordinates
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

// player paddle
class cPaddle
{
private:
    // position of the paddle
    int x, y;
    // the origin of the paddle when the game resets
    int originalX, originalY;

public:
    cPaddle()
    {
        // sets the position of the paddle to 0
        x = y = 0;
    }
    // limits the position of the paddle
    cPaddle(int posX, int posY) : cPaddle()
    {
        // keeps the start position of the paddle when game starts
        originalX = posX;
        originalY = posY;
        // sets the paddle equal an origin point when game starts or resets
        x = posX;
        y = posY;
    }
    // brings the players back to the start position
    inline void Reset()
    {
        x = originalX;
        y = originalY;
    }

    // returns x and y coordinates
    inline int getX() { return x; }
    inline int getY() { return y; }

    // moves the paddle up and down
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    // second paddle
    friend ostream &operator<<(ostream &o, cPaddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

// keeps track of the score of two players
class cGameManger
{
private:
    // sets a limit to how much a player can score before game ends
    int width, height;
    // scores of player one and two
    int score1, score2;
    // stores the symbol used to represent the paddles
    char up1, down1, up2, down2;
    // quits the program when the player presses a key
    bool quit;
    // initializes ball and paddles to players
    cBall *ball;
    cPaddle *player1;
    cPaddle *player2;

public:
    cGameManger(int w, int h)
    {
        // sets random numbers for the movement of the ball
        srand(time(NULL));

        // starts the game
        quit = false;

        // keybinds to move up or down for player 1 and player 2
        up1 = 'w';
        up2 = 'o';
        down1 = 's';
        down2 = 'k';

        // score starts at 0
        score1 = score2 = 0;
        // sets the boundary of the game
        width = w;
        height = h;
        // creates a new ball to spawn in the middle of the field after each round
        ball = new cBall(w / 2, h / 2);
        // creates a new paddles which spawn in the game near the middle left or middle right
        // after each round for player 1 and 2
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }
    // frees the memory of paddles and ball
    ~cGameManger()
    {
        delete ball, player1, player2;
    }
    // increase the score if the player scores a point
    void ScoreUp(cPaddle *player)
    {

        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        // resets the ball and player paddles to origin spawn point after each round
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw()
    {
        // clear screen
        system("cls");
        // print the boundaries of the game
        // create the length of the border
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        // create the height of border
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {

                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                // creates first vertical row of border
                if (j == 0)
                    cout << "#";
                // outputs image of ball
                if (ballx == j && bally == i)
                    cout << "[?]";
                // outputs image of paddles for player 1 and 2
                else if (player1x == j && player1y == i)
                    cout << "|";
                // outputs the rest of the paddle portion for player 1
                else if (player1x == j && player1y + 1 == i)
                    cout << "|";
                else if (player1x == j && player1y + 2 == i)
                    cout << "|";
                else if (player1x == j && player1y + 3 == i)
                    cout << "|";

                // outputs image of paddles for player 2
                else if (player2x == j && player2y == i)
                    cout << "|";
                // outputs the rest of the paddle portion for player 2
                else if (player2x == j && player2y + 1 == i)
                    cout << "|";
                else if (player2x == j && player2y + 2 == i)
                    cout << "|";
                else if (player2x == j && player2y + 3 == i)
                    cout << "|";
                else
                    cout << " ";
                // outputs the vertical game border
                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }
        // output the right border of the game
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        // outputs player score and quit option
        cout << "                        Welcome to a Game of PUCK\n"
             << "Player 1: " << score1 << endl
             << "Score 2: " << score2
             << "  "
             << "Press the key (q) to quit the game" << endl;
    }
    // creates ball movement within the game boundaries
    void Input()
    {
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        if (_kbhit())
        {
            // limits paddle within the ball
            // if the paddle is within the game border the paddle and move up or down
            char current = _getch();
            if (current == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (current == up2)
                if (player2y > 0)
                    player2->moveUp();
            if (current == down1)
                if (player1y + 4 < height)
                    player1->moveDown();
            if (current == down2)
                if (player2y + 4 < height)
                    player2->moveDown();
            // at the start of the game if a player presses an up or down key
            // the ball moves in a random direction
            if (ball->getDirection() == STOP)
                ball->randomDirection();
            // quits the game if user presses q
            if (current == 'q')
                quit = true;
        }
    }

    void Logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        // the left paddle for player 1
        for (int i = 0; i < 4; i++)
        {
            if (ballx == player1x + 1)
            {
                if (bally == player1y + i)
                {
                    // the ball changes a random direction if the ball hits the paddle
                    ball->changeDirection((eDir)((rand() % 3) + 4));
                }
            }
        }

        // the right paddle for player 2
        for (int i = 0; i < 4; i++)
        {
            if (ballx == player2x - 1)
            {
                if (bally == player2y + i)
                {
                    // the ball changes a random direction if the ball hits the paddle
                    ball->changeDirection((eDir)((rand() % 3) + 1));
                }
            }
        }
        // the ball bounces off bottom wall
        if (bally == height - 1)
        {
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }
        // the ball bounces off top wall
        if (bally == 0)
        {
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }
        // the ball bounces off the right wall
        if (ballx == width - 1)
        {
            // if bounces off right wall player 2 scores a point
            ScoreUp(player1);
        }
        // the ball bounces off the left wall
        if (ballx == 0)
        {
            // if bounces off left wall player 1 scores a point
            ScoreUp(player2);
        }
    }
    // program quit button
    void Run()
    {

        // the program will run as long as the user does not quit the program
        // by pressing q
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{

    cGameManger c(80, 25);
    c.Run();
    return 0;
}