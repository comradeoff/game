#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define HEIGHT 25
#define WIDTH 65

typedef struct{
    int x, y, w;
} TRacket;

char map[HEIGHT][WIDTH + 1];
TRacket racket;

void init_map() {
    for (int i = 0; i < WIDTH; i++) { map[0][i] = '#'; }
    map[0][WIDTH] = '\0';

    strncpy(map[1], map[0], WIDTH + 1);
    for (int i = 1; i < WIDTH - 1; i++) { map[1][i] = ' '; }

    for (int i = 2; i < HEIGHT; i++) { strncpy(map[i], map[1], WIDTH + 1); }
}

void init_racket() {
    racket.w = 7;
    racket.x = (WIDTH - racket.w) / 2;
    racket.y = HEIGHT - 1;
}

void put_racket() {
    for (int i = racket.x; i < racket.x + racket.w; i++) { map[racket.y][i] = '@'; }
}

void draw() {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s", map[i]);
        if (i < HEIGHT - 1) { printf("\n"); }
    }
}

void move_racket(int x) {
    racket.x = x;
    if (racket.x < 1) { racket.x = 1; }
    if (racket.x + racket.w >= WIDTH) { racket.x = WIDTH - 1 - racket.w; }
}

void setcur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
    init_racket();

    do {
        setcur(0, 0);

        init_map();
        put_racket();
        draw();

        if (GetKeyState('A') < 0) { move_racket(racket.x - 3); }
        if (GetKeyState('D') < 0) { move_racket(racket.x + 3); }
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}