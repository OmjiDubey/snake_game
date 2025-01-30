#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 

const int width = 1000;  // Window width
const int height = 700; // Window height
const int blockSize = 16; // Size of each block for snake and food
const int maxSnakeLength = 100; // Maximum snake length

struct Point {
    int x, y;
};

Point snake[maxSnakeLength]; // Snake body
int snakeLength = 3;         // Initial length
Point food;                  
int direction = 0;           // 0=right, 1=down, 2=left, 3=up

void initGame() {
    srand(time(0));
    initwindow(width, height, "Snake Game");

    // Initialize the snake position
    for (int i = 0; i < snakeLength; i++) {
        snake[i].x = (width / 2) - (i * blockSize);
        snake[i].y = height / 2;
    }

    // Place the initial food
    food.x = (rand() % (width / blockSize)) * blockSize;
    food.y = (rand() % (height / blockSize)) * blockSize;
}

void drawBlock(int x, int y, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x + blockSize, y + blockSize);
}

void drawGame() {
    cleardevice();

    // Draw the snake
    for (int i = 0; i < snakeLength; i++) {
        drawBlock(snake[i].x, snake[i].y, GREEN);
    }

    // Draw the food
    drawBlock(food.x, food.y, RED);

    // Update the screen
    delay(100);
}

void updateGame() {
    // Move the snake's body
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move the head based on the direction
    switch (direction) {
        case 0: snake[0].x += blockSize; break; // Right
        case 1: snake[0].y += blockSize; break; // Down
        case 2: snake[0].x -= blockSize; break; // Left
        case 3: snake[0].y -= blockSize; break; // Up
    }

    // Wrap around the screen
    if (snake[0].x >= width) snake[0].x = 0;
    if (snake[0].x < 0) snake[0].x = width - blockSize;
    if (snake[0].y >= height) snake[0].y = 0;
    if (snake[0].y < 0) snake[0].y = height - blockSize;

    // Check for collision with food
    if (abs(snake[0].x - food.x) < blockSize && abs(snake[0].y - food.y) < blockSize) {
        snakeLength++;
        food.x = (rand() % (width / blockSize)) * blockSize;
        food.y = (rand() % (height / blockSize)) * blockSize;
    }

    // Check for collision with itself
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            char sl = (char) snakeLength;
            outtextxy(width / 2 - 50, height / 2, const_cast<char*>("Game Over!"));

            // Display the final score below the "Game Over" message
            char scoreMessage[50];
            sprintf(scoreMessage, "Final Score: %d", snakeLength - 3);
            outtextxy(width / 2 - 70, height / 2 + 30, scoreMessage);

            getch();
            closegraph();
            exit(0);
        }
    }
    // delay(50);     //delay for slow speed
}

void handleInput() {
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'w': if (direction != 1) direction = 3; break;
            case 's': if (direction != 3) direction = 1; break;
            case 'a': if (direction != 0) direction = 2; break;
            case 'd': if (direction != 2) direction = 0; break;
        }
    }
}

int main() {
    initGame();

    while (true) {
        handleInput();
        updateGame();
        drawGame();
    }

    closegraph();
    return 0;
}
