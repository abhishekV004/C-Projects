// Header files
#include <iostream>
#include <conio.h>
#include <windows.h>

// Screen Size
#define H 21 // Height
#define W 51 // Width

using namespace std;

// Game entities and states
int collection = 0;         // Score
bool game_end = false;
int pY = 1, pX = 1;         // Player position
int e1Y = 1, e1X = W - 3;   // Enemy 1 position
int e2Y = H - 2, e2X = 1;   // Enemy 2 position

// Move console cursor to top-left without clearing screen
void setCursorPosition(short x, short y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hOut, pos);
}

// Draw the game screen with color
void draw_playfield(char playfield[H][W]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "\n\n\n";
    for (int i = 0; i < H; i++) {
        cout << "\t\t";
        for (int j = 0; j < W; j++) {
            char ch = playfield[i][j];
            switch (ch) {
                case '#': SetConsoleTextAttribute(hConsole, 10); break; // Green: Player
                case '@': SetConsoleTextAttribute(hConsole, 12); break; // Red: Enemy
                case '.': SetConsoleTextAttribute(hConsole, 14); break; // Yellow: Fruit
                case '*': SetConsoleTextAttribute(hConsole, 15); break; // White: Wall
                default:  SetConsoleTextAttribute(hConsole, 7);  break; // Gray: Empty
            }
            cout << ch;
        }
        cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, 7); // Reset color
    cout << "\t\t Score is " << collection << endl;
}

// Handle interactions and entity positions
void setup(char playfield[][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (playfield[i][j] == '#') playfield[i][j] = ' ';
            if (playfield[i][j] == '@') playfield[i][j] = '.';
        }
    }

    // Collect fruit
    if (playfield[pY][pX] == '.') {
        collection++;
        playfield[pY][pX] = ' ';
    }

    // Collision with wall resets player
    if (playfield[pY][pX] == '*') {
        pY = 1;
        pX = 1;
    }

    // Collision with enemy ends game
    if ((pY == e1Y && pX == e1X) || (pY == e2Y && pX == e2X)) {
        game_end = true;
        return;
    }

    // Update positions
    playfield[pY][pX] = '#';
    playfield[e1Y][e1X] = '@';
    playfield[e2Y][e2X] = '@';
}

// Show result screen
void result() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n";
    if (collection >= 670) {
        cout << "\t\t\t           Congratulations!\n";
        cout << "\t\t\t          You won the game!\n";
    } else {
        cout << "\t\t\t          You lost the game!\n";
    }
    cout << "\t\t\t         Your total score is " << collection << endl;
}

// Move enemies in a pattern
void enemyMove() {
    // Enemy 1
    if (e1Y == 1 && e1X > 1) e1X--;
    else if (e1X == 1 && e1Y < 10) e1Y++;
    else if (e1Y == 10 && e1X < W - 3) e1X++;
    else if (e1X == W - 3 && e1Y > 1) e1Y--;

    // Enemy 2
    if (e2Y == H - 2 && e2X < W - 3) e2X++;
    else if (e2X == W - 3 && e2Y > 10) e2Y--;
    else if (e2Y == 10 && e2X > 1) e2X--;
    else if (e2X == 1 && e2Y < H - 2) e2Y++;
}

// Move player using arrow keys
void playerMove() {
    if (kbhit()) {
        char ch = getch();
        switch (ch) {
            case 72: if (pY > 0) pY--; break;      // Up
            case 80: if (pY < H - 1) pY++; break;  // Down
            case 75: if (pX > 0) pX--; break;      // Left
            case 77: if (pX < W - 1) pX++; break;  // Right
        }
    }
}

int main() {
    // Game layout
    char playfield[H][W] = {
        "**************************************************",
        "*................................................*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*................................................*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*..*..*..*..*..*..*..*..*..*..*..*..*..*..*..*...*",
        "*................................................*",
        "**************************************************"
    };

    // Game loop
    while (!game_end) {
        setCursorPosition(0, 0);      // Move cursor to top-left
        setup(playfield);             // Update entities
        playerMove();                 // Move player
        enemyMove();                  // Move enemies
        draw_playfield(playfield);    // Draw the field
        Sleep(20);                    // Frame delay (adjustable)
    }

    result(); // Show final screen
    return 0;
}














https://github.com/abhishekV004/C-Projects.git