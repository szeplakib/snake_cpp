#include <iostream>
#include "Snake.h"
#include <windows.h>


using namespace std;

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    } else {
        COORD invalid = {0, 0};
        return invalid;
    }
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void resetCursor(int n){
    COORD coord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
    coord.Y = coord.Y - (MAP_HEIGHT + 1) + n;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << flush;
}

int main() {
    ShowConsoleCursor(false);
    Snake snake = Snake();
    snake.set_start();
    bool x = true;
    while (x) {
        if( GetAsyncKeyState( VK_UP ) & 0x8000 ) {
            snake.go(VK_UP);
        } else if ( GetAsyncKeyState( VK_DOWN ) & 0x8000 ) {
            snake.go(VK_DOWN);
        } else if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 ) {
            snake.go(VK_LEFT);
        }else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 ) {
            snake.go(VK_RIGHT);
        }else
            snake.go();
        Sleep(100 - (snake.getSnakeLength()-3));
        snake.reDraw();
        cout << "Score: " << snake.getSnakeLength()-3 << endl;
        cout << snake;
        if (snake.isDead()){
            resetCursor(0);
            cout << "Game Over!" << endl;
            cout << "Final Score: " << snake.getSnakeLength()-3;
            snake.deDraw(1);
            cout << snake;
            resetCursor(1);
            return 0;
        }
        resetCursor(0);
    }
}