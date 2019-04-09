#include <stdlib.h>

#include "modes.h"
#include "game.h"
#include "animations.h"
#include "extras.h"
#include <curses.h>
#include <pthread.h>

void feed(Game *game, pthread_mutex_t mutex) {

}
void lite(Game *game, pthread_mutex_t mutex) {
    int ch;
    int opt = 0;
    pthread_mutex_lock(&mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    draw_other(yes, 4, 10, game);
    draw_other(no, 10, 13, game);
    draw_other(arrow, 4, 2, game);
    //refresh();*/
    //pthread_mutex_unlock(&mutex);
    //ch = getchar();
    //mvaddstr(ch, 4, 4);
    refresh();
    pthread_mutex_unlock(&mutex);
    while((ch = getch()) != 'n') {
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT) || (ch == 'b')) {
            if (opt == 0) {
                opt++;
                pthread_mutex_lock(&mutex);
                draw_other(blank_arrow, 4, 2, game);
                draw_other(arrow, 10, 2, game);
                refresh();
                game->light = 1;
                pthread_mutex_unlock(&mutex);
            } else if (opt == 1) {
                opt--;
                pthread_mutex_lock(&mutex);
                draw_other(arrow, 4, 2, game);
                draw_other(blank_arrow, 10, 2, game);
                refresh();
                game->light = 0;
                pthread_mutex_unlock(&mutex);
            }
        } else if (ch == 'm') {
            break;
        }
    //ch = getch();
    }
    pthread_mutex_lock(&mutex);
    //if (ch == 'n') {
        //draw_other(arrow, 4, 2, game);
        //draw_other(blank_arrow, 10, 2, game);
        //refresh();
    //}
    if (ch != 'm') {
        if (opt == 1) {
            // draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
            game->light = 1;
        } else if (opt == 0) {
            draw_other(clear_screen, 3, 0, game);
            game->light = 0;
        }
        refresh();
    } else {
        if (game->light == 0) {
            // draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
        } else if (game->light == 1) {
            draw_other(clear_screen, 3, 0, game);
        }
        refresh();
    }
    game->busy = 1;
    pthread_mutex_unlock(&mutex);


}
void play(Game *game, pthread_mutex_t mutex) {
    int ch;
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    while(ch = getch() != 'm') {
        attron(COLOR_PAIR(3));
        pthread_mutex_lock(&mutex);
        draw_other(zero, 3, 2, game);
        pthread_mutex_unlock(&mutex);
        attroff(COLOR_PAIR(3));
        attron(COLOR_PAIR(4));
        pthread_mutex_lock(&mutex);
        draw_other(zero, 3, 29, game);
        pthread_mutex_unlock(&mutex);
        attroff(COLOR_PAIR(4));
    }
}

void meds(Game *game, pthread_mutex_t mutex) {

}

void duck(Game *game, pthread_mutex_t mutex) {

}

void hlth(Game *game, pthread_mutex_t mutex) {

}

void disc(Game *game, pthread_mutex_t mutex) {

}

void attn(Game *game, pthread_mutex_t mutex) {

}
