#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    const int HEIGHT = 15, WIDTH = 30;
    char map[HEIGHT][WIDTH + 1];

    int player_x = 5;
    int player_y = 10;
    int ox, oy;
    int apple_x = 5, apple_y = 6;

    char key;
    int score = 0;

    do {
        sprintf(map[0], "##############################");
        for (int i = 1; i < HEIGHT - 1; i++) { sprintf(map[i], "#                            #"); }
        sprintf(map[HEIGHT - 1], "##############################");

        map[player_y][player_x] = '@';
        map[apple_y][apple_x] = '&';

        system("cls");
        for (int i = 0; i < HEIGHT; i++) { printf("%s\n", map[i]); }

        key = getch();

        ox = player_x; oy = player_y;

        if (key == 'w') { player_y--; }
        if (key == 's') { player_y++; }
        if (key == 'a') { player_x--; }
        if (key == 'd') { player_x++; }

        if (map[player_y][player_x] == '#') { player_x = ox; player_y = oy; }

        if ((player_x == apple_x) && (player_y == apple_y)) {
            apple_x = rand() % (WIDTH - 1) + 1;
            apple_y = rand() % (HEIGHT - 1) + 1;
            score++;
        }

        printf("Score: %d", score);

    }
    while (key != 'c');


    return 0;
}


