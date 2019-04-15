#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "camagotchi.h"
#include "animations.h"
#include "border.h"
#include "modes.h"
#include <signal.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void init_screen(Game *game) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        free(game);
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    mvaddstr(0, 0, outline());
    insert_options();
    refresh();
}

void *wait_for_input(void *vgame) {
    Game *game = (Game *) vgame; 
    int ch = '\0';
    while (ch != 'o') {
        if (game->busy == 1) {
            ch = getch();
            if ((ch == KEY_LEFT) || (ch == KEY_RIGHT) || (ch == 'b')) {
                pthread_mutex_lock(&mutex);
                move_cursor(game, ch);
                refresh();
                pthread_mutex_unlock(&mutex);
            } else if ((ch == KEY_ENTER) || (ch == 'n')) {
                change_mode(game, mutex);
            }
        }
    }
    pthread_exit(NULL);
}

void *animation(void *vgame) {
    Game *game = (Game *) vgame;
    Animations *animations = malloc(sizeof(Animations));
    animations = init_animations();
    while(1) {
        if ((game->light != 1) && (game->busy != 0)) {
            switch(game->stage) {
                case 0:
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->egg_rotate1, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->egg_rotate2, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->egg_rotate3, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->egg_rotate4, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->egg_rotate5, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    break;
                case 1:
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage1, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage2, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage1, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage3, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage4, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->stage3, 10, 14, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    break;
                case 2:
                    break;
                case 3:
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->dance1, 3, 8, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    pthread_mutex_lock(&mutex);
                    draw_sprite(animations->dance2, 3, 8, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    usleep(500000);
                    break;
            }
        }
    }
    pthread_exit(NULL);
}

void *growth(void *vgame) {
    Game *game = (Game *) vgame; 
    usleep(20000000);
    pthread_mutex_lock(&mutex);
    game->stage++;
    pthread_mutex_unlock(&mutex);
    usleep(20000000);
    pthread_mutex_lock(&mutex);
    game->stage = 3;
    pthread_mutex_unlock(&mutex);
    while(1)
        pthread_exit(NULL);
}

void create_threads(Game *game) {
    pthread_t threads[10];
    void* ret;
    pthread_create(&threads[0], NULL, wait_for_input, (void *) game);
    pthread_create(&threads[1], NULL, animation, (void *) game);
    pthread_create(&threads[2], NULL, growth, (void *) game);
    for (int j = 0; j < 1; j++) {
        pthread_join(threads[j], &ret);
    }
}

void destroy_game() {
    cbreak();
    endwin();
    exit(EXIT_SUCCESS);

}

void destroy_signal(int signals) {
    signal(signals, SIG_IGN);
    destroy_game();
}

int main() {
    Game *game = malloc(sizeof(Game));
    game->current_option = 0;
    game->stage = 0;
    game->light = 0;
    game->busy = 1;
    game->cam = malloc(sizeof(Camagotchi));
    srand(time(NULL));
    init_screen(game);
    signal(SIGINT, destroy_signal);
    keypad(stdscr, TRUE);
    int ch;
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    create_threads(game);
    destroy_game();
    return EXIT_SUCCESS;
}
