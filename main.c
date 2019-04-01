#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include "camagotchi.h"
#include "animations.h"
#include "border.h"
#include "game.h"
#include <signal.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*typedef struct Game {
    int x;
    int end;
    int flag;
    int current_option;
} Game;
*/
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
    mvaddstr(0, 0, outline());
    attron(COLOR_PAIR(1));
    mvaddstr(1, 1, "      ");
    attroff(COLOR_PAIR(1));
    refresh();
}

void draw_sprite(char *to_print, int row, int col) {
    char *tok;
    char *string = strdup(to_print); 
    tok = strtok(string, "\n");
    while (tok != NULL) {
        mvaddstr(row, col, tok);
        tok = strtok(NULL, "\n");
        row++;
    }
    
}

void *wait_for_input(void *vgame) {
    Game *game = (Game *) vgame; 
    int ch;
    while((ch = getch()) != 'o') {
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT)) {
            pthread_mutex_lock(&mutex);
            move_cursor(game, ch);
            refresh();
            pthread_mutex_unlock(&mutex);
        }
    }
    //game->flag = 0;//
    pthread_exit(NULL);
}

void *animation(void *vgame) {
    //mvprintw(0, 0, "%d", getpid());
    //getch();
    Game *game = (Game *) vgame;
    // Animations *animations = init_animations();
    Animations *animations = malloc(sizeof(Animations));
    animations = init_animations();
    while(1) {
        switch(game->stage) {
            case 0:
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->egg1, 10, 10);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->egg2, 10, 10);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->egg1, 10, 10);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->egg3, 10, 10);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->dance1, 3, 4);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                pthread_mutex_lock(&mutex);
                draw_sprite(animations->dance2, 3, 4);
                refresh();
                pthread_mutex_unlock(&mutex);
                usleep(500000);
                break;
        }
    }
    pthread_exit(NULL);
}

void *growth(void *vgame) {
    Game *game = (Game *) vgame; 
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
    // pthread_create(&threads[1], NULL, wait_for_input, (void *) game);
    // pthread_create(&threads[0], NULL, animations, (void *) game);
    //while((ch = getch()) != 'o') {
    //}
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
    //initscr();
    //cbreak();
    //noecho();
    Game *game = malloc(sizeof(Game));
    game->current_option = 0;
    game->stage = 0;
    init_screen(game);
    //while(1);
    // Animations *animations = init_animations();
    signal(SIGINT, destroy_signal);
    keypad(stdscr, TRUE);
    int ch;
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);
    create_threads(game);
    destroy_game();
    return EXIT_SUCCESS;
}
