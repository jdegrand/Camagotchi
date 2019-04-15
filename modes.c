#include <stdlib.h>

#include "modes.h"
#include "camagotchi.h"
#include "animations.h"
#include "extras.h"
#include <curses.h>
#include <pthread.h>

void feed(Game *game, pthread_mutex_t mutex) {
    int ch;
    int opt = 0;
    pthread_mutex_lock(&mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    draw_other(meal, 4, 7, game);
    draw_other(snack, 10, 7, game);
    draw_other(small_arrow, 4, 1, game);
    refresh();
    pthread_mutex_unlock(&mutex);
    while((ch = getch()) != 'n') {
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT) || (ch == 'b')) {
            if (opt == 0) {
                opt++;
                pthread_mutex_lock(&mutex);
                draw_other(small_blank_arrow, 4, 1, game);
                draw_other(small_arrow, 10, 1, game);
                refresh();
                pthread_mutex_unlock(&mutex);
            } else if (opt == 1) {
                opt--;
                pthread_mutex_lock(&mutex);
                draw_other(small_arrow, 4, 1, game);
                draw_other(small_blank_arrow, 10, 1, game);
                refresh();
                pthread_mutex_unlock(&mutex);
            }
        } else if (ch == 'm') {
            break;
        }
    }
    pthread_mutex_lock(&mutex);
    draw_other(clear_screen, 3, 0, game);
    refresh();
    pthread_mutex_unlock(&mutex);
    game->busy = 1;

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
                pthread_mutex_unlock(&mutex);
            } else if (opt == 1) {
                opt--;
                pthread_mutex_lock(&mutex);
                draw_other(arrow, 4, 2, game);
                draw_other(blank_arrow, 10, 2, game);
                refresh();
                pthread_mutex_unlock(&mutex);
            }
        } else if (ch == 'm') {
            break;
        }
    }
    pthread_mutex_lock(&mutex);
    if (ch != 'm') {
        if (opt == 1) {
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
        if (game->light == 1) {
            // draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            draw_other(clear_screen, 3, 0, game);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(1));
        } else if (game->light == 0) {
            draw_other(clear_screen, 3, 0, game);
        }
        refresh();
    }
    game->busy = 1;
    pthread_mutex_unlock(&mutex);
}

void draw_number(int random, int col, Game *game) {
    switch(random) {
        case 0:
            draw_other(zero, 3, col, game);
            break;
        case 1:
            draw_other(one, 3, col, game);
            break;
        case 2:
            draw_other(two, 3, col, game);
            break;
        case 3:
            draw_other(three, 3, col, game);
            break;
        case 4:
            draw_other(four, 3, col, game);
            break;
        case 5:
            draw_other(five, 3, col, game);
            break;
        case 6:
            draw_other(six, 3, col, game);
            break;
        case 7:
            draw_other(seven, 3, col, game);
            break;
        case 8:
            draw_other(eight, 3, col, game);
            break;
        case 9:
            draw_other(nine, 3, col, game);
            break;
    }
}

int valid_key(int ch) {
    switch(ch) {
        case 'b':
            return 1;
        case 'n':
            return 1;
        case 'm':
            return 1;
        case KEY_LEFT:
            return 1;
        case KEY_RIGHT:
            return 1;
        default:
            return 0;
    }
}

void play(Game *game, pthread_mutex_t mutex) {
    int ch;
    int random;
    init_pair(3, COLOR_CYAN, COLOR_WHITE);
    init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
    pthread_mutex_lock(&mutex);
    random = rand() % 10;
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    //game->busy = 0;
    draw_number(random, 2, game);
    refresh();
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    pthread_mutex_unlock(&mutex);
    ch = getch();
    while (!(valid_key(ch))) {
        ch = getch();
    }
    if (ch == 'm') {
        pthread_mutex_lock(&mutex);
        draw_other(clear_screen, 3, 0, game);
        refresh();
        pthread_mutex_unlock(&mutex);
        return; 
    }
    pthread_mutex_lock(&mutex);
    random = rand() % 10;
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(4));
    draw_number(random, 29, game);
    refresh();
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    usleep(2500000);
    //game->busy = 1;
    draw_other(clear_screen, 3, 0, game);
    refresh();
    pthread_mutex_unlock(&mutex);
}

void meds(Game *game, pthread_mutex_t mutex) {

}

void duck(Game *game, pthread_mutex_t mutex) {

}

void draw_hearts(int value, int row, int col, Game *game) {
    for (int i = 0; i <=3; i++) {
        if (value == 1) {
            draw_other(half_heart, row, col, game);
            value--;
        }
        else if (value <= 0) {
            draw_other(blank_heart, row, col, game); 
        } else {
            draw_other(full_heart, row, col, game); 
            value -= 2;
        }
        col += 8;
    }
}

void hlth(Game *game, pthread_mutex_t mutex) {
    int ch;
    int opt = 0;
    pthread_mutex_lock(&mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    /*draw_other(full_heart, 3, 3, game);
    draw_other(full_heart, 3, 11, game);
    draw_other(full_heart, 3, 19, game);
    draw_other(full_heart, 3, 27, game);*/
    draw_other(happy, 4, 4, game);
    //draw_other(full_heart, 3, 27, game);
    draw_hearts(4 ,10, 3, game);
    refresh();
    pthread_mutex_unlock(&mutex);
    while((ch = getch()) != 'm') {
        if ((ch == KEY_RIGHT) || (ch == 'b')) {
            opt++;
            if (opt == 4) {
                opt = 0;
            }
            switch(opt) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    pthread_mutex_lock(&mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(hungry, 4, 7, game);
                    draw_hearts(4 , 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    break;
                case 3:
                    pthread_mutex_lock(&mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(happy, 4, 4, game);
                    draw_hearts(4, 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(&mutex);
                    break;
            }
        }
    }
    pthread_mutex_lock(&mutex);
    draw_other(clear_screen, 3, 0, game);
    refresh();
    game->busy = 1;
    pthread_mutex_unlock(&mutex);
}

void disc(Game *game, pthread_mutex_t mutex) {

}

void attn(Game *game, pthread_mutex_t mutex) {

}
