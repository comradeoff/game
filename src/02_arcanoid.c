#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define HEIGHT 25
#define WIDTH 65

struct Racket{
    int x, y, w;
};

struct Ball {
    float x, y;
    int ix, iy;
    float alpha;
    float speed;
};

char map[HEIGHT][WIDTH + 1];
struct Racket racket;
struct Ball ball;
int hit_cnt = 0;

void init_ball() {
    move_ball(2, 2);
    ball.alpha = -1;
    ball.speed = 1.5f;
}

void put_ball() {
    map[ball.iy][ball.ix] = '*';
}

void init_map() {
    for (int i = 0; i < WIDTH; i++) { map[0][i] = '#'; }
    map[0][WIDTH] = '\0';

    strncpy(map[1], map[0], WIDTH + 1);
    for (int i = 1; i < WIDTH - 1; i++) { map[1][i] = ' '; }

    for (int i = 2; i < HEIGHT; i++) { strncpy(map[i], map[1], WIDTH + 1); }
}

void move_ball(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void auto_move_ball() {
    if (ball.alpha < 0) { ball.alpha += M_PI*2; }
    if (ball.alpha > M_PI*2) { ball.alpha -= M_PI*2; }

    struct Ball tmp = ball;
    move_ball(ball.x + cos(ball.alpha) * ball.speed,
              ball.y + sin(ball.alpha) * ball.speed);

    if ((map[ball.iy][ball.ix] == '#') || (map[ball.iy][ball.ix] == '@')) {
        if (map[ball.iy][ball.ix] == '@') { hit_cnt++; }

        if ((ball.ix != tmp.ix) && (ball.iy != tmp.iy)) {
            if (map[tmp.iy][ball.ix] == map[ball.iy][tmp.ix]) { tmp.alpha = tmp.alpha + M_PI; }
            else {
                if (map[tmp.iy][ball.ix] == '#') { tmp.alpha = (2*M_PI - tmp.alpha) + M_PI; }
                else { tmp.alpha = (2*M_PI - tmp.alpha); }
            }
        }
        else if (ball.iy == tmp.iy) { tmp.alpha = (2*M_PI - tmp.alpha) + M_PI; }
        else { tmp.alpha = (2*M_PI - tmp.alpha); }

        ball = tmp;
        auto_move_ball();
    }
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
    BOOL run = FALSE;
    init_racket();
    init_ball();

    do {
        setcur(0, 0);

        init_map();
        put_racket();
        put_ball();
        draw();

        if (run) { auto_move_ball(); }
        if (ball.iy > HEIGHT) { run = FALSE; hit_cnt = 0; }

        if (GetKeyState('A') < 0) { move_racket(racket.x - 3); }
        if (GetKeyState('D') < 0) { move_racket(racket.x + 3); }
        if (GetKeyState('W') < 0) { run = TRUE; }
        if (!run) { move_ball(racket.x + racket.w / 2, racket.y - 1); }

        printf("Hits: %i\n", hit_cnt);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    system("pause");
    return 0;
}
