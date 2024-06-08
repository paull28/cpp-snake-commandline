#include <iostream>
#include <windows.h>
#include <conio.h>

// Width, height of boundary
const int width = 80;
const int height = 20;

// Coordinates of fruits
int fruitX, fruitY;

// Score, game over
int score;
bool isGameOver;

// Coordinates of snake head
int x, y;

// Array to hold coordinates of snake tail, and length
int snakeTailX[100], snakeTailY[100];
int snakeTailLen;

// Direction of snake
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir;

// Initialise game
void GameInit() {
    isGameOver = false; // start game
    sDir = STOP; // init dir
    x = width / 2; // Set snake to middle
    y = height / 2; // Set snake to middle
    fruitX = rand() % width;  // Randomise fruit coords
    fruitY = rand() % height; // Randomise fruit coords
    score = 0; // init score
}

// Render game, inc. borders, snake head + tail and fruit
void GameRender(std::string playername) {
    system("cls"); // Clear console

    // Top border
    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;

    // Side borders, snake + tail and fruit
    for(int i = 0; i < height; i++){
        for(int j = 0; j <= width; j++){
            // Side walls
            if(j== 0 || j == width){
                std::cout << "|";
            }
            // Snake head
            if(i==y && j==x){
                std::cout << "O";
            }
            // Fruit
            else if(i==fruitY && j==fruitX){
                std::cout << "$";
            }
            // Tail
            else {
                bool prTail = false;
                for(int k=0; k < snakeTailLen; k++) {
                    if(snakeTailX[k] == j && snakeTailY[k] == i){
                        std::cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // Bottom border
    for (int i = 0; i < width+2; i++){
        std::cout << "-";
    }
    std::cout << std::endl;

    // score
    std::cout << playername << "'s score: " << score << std::endl;
}

// update game state
void UpdateGame() {

    // Update snake
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++){
        int prev2x = snakeTailX[i];
        int prev2y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2x;
        prevY = prev2y;
    }

    // Switch case
    switch(sDir) {
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
    }

    // Collision with border
    if (x >= width || x < 0 || y >= height || y < 0){
        isGameOver = true;
    }
    // Collision with tail
    for (int i = 0; i<snakeTailLen; i++){
        if (snakeTailX[i] == x && snakeTailY[i] == y){
            isGameOver = true;
        }
    }
    // Collision with food
    if (x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snakeTailLen++;
    }
}

void UserInput() {
    if (_kbhit()){
        switch (_getch())
        {
        case 'a':
            sDir= LEFT;
            break;
        case 'd':
            sDir= RIGHT;
            break;
        case 's':
            sDir= DOWN;
            break;
        case 'w':
            sDir= UP;
            break;
        case 'x': // x for exit
            isGameOver = true;
            break;
        }
    }
}

int main() 
{ 
    std::string playerName; 
    std::cout << "enter your name: "; 
    std::cin >> playerName;  
  
    GameInit(); 
    while (!isGameOver) { 
        GameRender(playerName); 
        UserInput(); 
        UpdateGame(); 
        Sleep(75);
    } 
  
    return 0; 
}