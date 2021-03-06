#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include "modes.h"
#include "camagotchi.h"
#include "animations.h"
#include "extras.h"
#include <curses.h>
#include <pthread.h>

void increment_happy(Game *game, int amount) {
    (game->cam)->happy += amount;
    if ((game->cam)->happy > 8) {
        (game->cam)->happy = 8;
    }
}

void decrement_happy(Game *game, int amount) {
    (game->cam)->happy -= amount;
    if ((game->cam)->happy < 0) {
        (game->cam)->happy = 0;
    }
}

void decrement_hunger(Game *game, int amount) {
    (game->cam)->hunger -= amount;
    if ((game->cam)->hunger < 0) {
        (game->cam)->hunger = 0;
    }
}

void feed(Game *game, pthread_mutex_t *mutex) {
    int ch;
    int opt = 0;
    int random;
    pthread_mutex_lock(mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    draw_other(meal, 4, 7, game);
    draw_other(snack, 10, 7, game);
    draw_other(small_arrow, 4, 1, game);
    refresh();
    pthread_mutex_unlock(mutex);
    while((ch = getch()) != 'n') {
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT) || (ch == 'b')) {
            if (opt == 0) {
                opt++;
                pthread_mutex_lock(mutex);
                draw_other(small_blank_arrow, 4, 1, game);
                draw_other(small_arrow, 10, 1, game);
                refresh();
                pthread_mutex_unlock(mutex);
            } else if (opt == 1) {
                opt--;
                pthread_mutex_lock(mutex);
                draw_other(small_arrow, 4, 1, game);
                draw_other(small_blank_arrow, 10, 1, game);
                refresh();
                pthread_mutex_unlock(mutex);
            }
        } else if (ch == 'm') {
            break;
        }
    }
    if (ch != 'm') {
        switch(opt) {
            case 0:
                (game->cam)->hunger += 2;
                (game->cam)->weight += 1;
                // random = 1;
                random = rand() % 8;
                if (random == 1) {
                    pthread_mutex_lock(mutex);
                    (game->cam)->poop_left = 1;
                    pthread_mutex_unlock(mutex);
                }
                break;
            case 1:
                (game->cam)->hunger += 1;
                (game->cam)->weight += 2;
                random = rand() % 8;
                // random = 1;
                if (random == 1) {
                    pthread_mutex_lock(mutex);
                    (game->cam)->poop_right = 1;
                    //draw_other(poop_left, 10, 1, game);
                    //refresh();
                    pthread_mutex_unlock(mutex);
                }
                break;
        }
    }
    if ((game->cam)->hunger > 8) {
        pthread_mutex_lock(mutex);
        (game->cam)->sick = 1;
        (game->cam)->hunger = 8;
        decrement_happy(game, 4);
        pthread_mutex_unlock(mutex);
    }
    pthread_mutex_lock(mutex);
    draw_other(clear_screen, 3, 0, game);
    refresh();
    pthread_mutex_unlock(mutex);
    game->busy = 1;
}

void lite(Game *game, pthread_mutex_t *mutex) {
    int ch;
    int opt = 0;
    pthread_mutex_lock(mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    draw_other(yes, 4, 10, game);
    draw_other(no, 10, 13, game);
    draw_other(arrow, 4, 2, game);
    refresh();
    pthread_mutex_unlock(mutex);
    while((ch = getch()) != 'n') {
        if ((ch == KEY_LEFT) || (ch == KEY_RIGHT) || (ch == 'b')) {
            if (opt == 0) {
                opt++;
                pthread_mutex_lock(mutex);
                draw_other(blank_arrow, 4, 2, game);
                draw_other(arrow, 10, 2, game);
                refresh();
                pthread_mutex_unlock(mutex);
            } else if (opt == 1) {
                opt--;
                pthread_mutex_lock(mutex);
                draw_other(arrow, 4, 2, game);
                draw_other(blank_arrow, 10, 2, game);
                refresh();
                pthread_mutex_unlock(mutex);
            }
        } else if (ch == 'm') {
            break;
        }
    }
    pthread_mutex_lock(mutex);
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
    pthread_mutex_unlock(mutex);
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

void play(Game *game, pthread_mutex_t *mutex) {
    int ch;
    int random;
    init_pair(3, COLOR_CYAN, COLOR_WHITE);
    init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
    pthread_mutex_lock(mutex);
    random = rand() % 10;
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    //game->busy = 0;
    draw_number(random, 2, game);
    refresh();
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    pthread_mutex_unlock(mutex);
    ch = getch();
    while (!(valid_key(ch))) {
        ch = getch();
    }
    if (ch == 'm') {
        pthread_mutex_lock(mutex);
        draw_other(clear_screen, 3, 0, game);
        refresh();
        pthread_mutex_unlock(mutex);
        return; 
    }
    pthread_mutex_lock(mutex);
    int random2 = rand() % 10;
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(4));
    draw_number(random2, 29, game);
    refresh();
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(1));
    if ((ch == 'n') || (ch == KEY_RIGHT)) {
        if (random2 >= random) {
            increment_happy(game, 1);
        }
    } else if ((ch == 'b') || (ch == KEY_LEFT)) { 
        if (random2 <= random) {
            increment_happy(game, 1);
        }
    }
    pthread_mutex_unlock(mutex);
    usleep(2500000);
    pthread_mutex_lock(mutex);
    //game->busy = 1;
    draw_other(clear_screen, 3, 0, game);
    refresh();
    pthread_mutex_unlock(mutex);
}

void meds(Game *game, pthread_mutex_t *mutex) {
    // game->stage
    if ((game->cam)->sick != 1) {
        pthread_mutex_lock(mutex);
        decrement_happy(game, 1);
        pthread_mutex_unlock(mutex);
        return;
    }
    switch(game->stage) {
        case 1:
            pthread_mutex_lock(mutex);
            draw_other(syringe, 9, 21, game);
            refresh();
            //pthread_mutex_unlock(&mutex);
            usleep(500000);
            //pthread_mutex_lock(&mutex);
            draw_other(clear_sick, 9, 21, game);
            refresh();
            pthread_mutex_unlock(mutex);
            break;
        case 2:
            break;
        case 3:
            pthread_mutex_lock(mutex);
            draw_other(syringe, 3, 24, game);
            refresh();
            //pthread_mutex_unlock(&mutex);
            usleep(500000);
            //pthread_mutex_lock(&mutex);
            draw_other(clear_sick, 3, 24, game);
            refresh();
            pthread_mutex_unlock(mutex);
            break;
    }
    int random = rand() % 3;
    if (random == 1) {
        pthread_mutex_lock(mutex);
        (game->cam)->sick = 0;
        pthread_mutex_unlock(mutex);
    }
}

void duck(Game *game, pthread_mutex_t *mutex) {
    int first_time = 1;
    pthread_mutex_lock(mutex);
    // game->busy = 0;
    (game->cam)->poop_left = 0;
    (game->cam)->poop_right = 0;
    pthread_mutex_unlock(mutex);
    for (int i = 32; i > 0; i--) {
        pthread_mutex_lock(mutex);
        draw_other(sweep, 3, i, game);
        if (first_time == 0) {
            draw_other(clear_sweep, 3, i + 4, game);
        } else {
            first_time = 0;
        }
        refresh();
        pthread_mutex_unlock(mutex);
        usleep(100000);
    }
    pthread_mutex_lock(mutex);
    draw_other(clear_sweep, 3, 4, game);
    draw_other(clear_sweep, 3, 3, game);
    draw_other(clear_sweep, 3, 2, game);
    draw_other(clear_sweep, 3, 1, game);
    refresh();
    // game->busy = 1;
    pthread_mutex_unlock(mutex);
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

void hlth(Game *game, pthread_mutex_t *mutex) {
    int ch;
    int opt = 0;
    pthread_mutex_lock(mutex);
    game->busy = 0;
    draw_other(clear_screen, 3, 0, game);
    draw_other(happy, 4, 4, game);
    draw_hearts((game->cam)->happy ,10, 3, game);
    refresh();
    pthread_mutex_unlock(mutex);
    while((ch = getch()) != 'm') {
        if ((ch == KEY_RIGHT) || (ch == 'b')) {
            opt++;
            if (opt == 2) {
                opt = 0;
            }
            switch(opt) {
                case 0:
                    pthread_mutex_lock(mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(happy, 4, 4, game);
                    draw_hearts((game->cam)->happy, 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(mutex);
                    //opt = 2;
                    break;
                case 1:
                    pthread_mutex_lock(mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(hungry, 4, 7, game);
                    draw_hearts((game->cam)->hunger , 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(mutex);
                    //opt = 3;
                    break;
                case 2:
                    pthread_mutex_lock(mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(hungry, 4, 7, game);
                    draw_hearts((game->cam)->hunger , 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(mutex);
                    break;
                case 3:
                    pthread_mutex_lock(mutex);
                    draw_other(clear_screen, 3, 0, game);
                    draw_other(happy, 4, 4, game);
                    draw_hearts((game->cam)->happy, 10, 3, game);
                    refresh();
                    pthread_mutex_unlock(mutex);
                    break;
            }
        }
    }
    pthread_mutex_lock(mutex);
    draw_other(clear_screen, 3, 0, game);
    refresh();
    game->busy = 1;
    pthread_mutex_unlock(mutex);
}

void disc(Game *game, pthread_mutex_t *mutex) {

}

void attn(Game *game, pthread_mutex_t *mutex) {
    if ((game->cam)->attention == 1) {
        pthread_mutex_lock(mutex);
        (game->cam)->attention = 0;
        pthread_mutex_unlock(mutex);
    }
}
