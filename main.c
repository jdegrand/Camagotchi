#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include "camagotchi.h"
#include "animations.h"
#include <signal.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct Game {
    int x;
    int end;
    int flag;
} Game;

void init_screen() {
    initscr();
    cbreak();
    noecho();
}

void *wait_for_input(void *vgame) {
    Game *game = (Game *) vgame; 
    int ch;
    while((ch = getch()) != 'o') {
        pthread_mutex_lock(&mutex);
        mvaddstr(0, 60, ch);
        refresh();
        //game->flag = 0;
        pthread_mutex_unlock(&mutex);
    }
    //game->flag = 0;//
    pthread_exit(NULL);
}

void *animation(void *vgame) {
    mvprintw(0, 0, "%d", getpid());
    getch();
    Game *game = (Game *) vgame;
    // Animations *animations = init_animations();
    Animations *animations = malloc(sizeof(Animations));
    animations = init_animations();
    while(1) {
        pthread_mutex_lock(&mutex);
        mvaddstr(0,0, animations->dance1);
        //mvaddstr(0,0, "111111111");
        refresh();
        pthread_mutex_unlock(&mutex);
        usleep(500000);
        pthread_mutex_lock(&mutex);
        mvaddstr(0,0, animations->dance2);
        //mvaddstr(0,0, "000000000");
        refresh();
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
}

void create_threads(Game *game) {
    pthread_t threads[10];
    void* ret;
    pthread_create(&threads[0], NULL, wait_for_input, (void *) game);
    pthread_create(&threads[1], NULL, animation, (void *) game);
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
    initscr();
    cbreak();
    noecho();
    Game *game = malloc(sizeof(Game));
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
