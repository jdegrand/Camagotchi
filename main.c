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
#include "extras.h"
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
                change_mode(game, &mutex);
                pthread_mutex_lock(&mutex);
                flushinp();
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    pthread_exit(NULL);
}

void *animation(void *vgame) {
    Game *game = (Game *) vgame;
    Animations *animations = malloc(sizeof(Animations));
    animations = game->animations;
    int random;
    int hunger_mod;
    int happy_mod;
    int sick_mod;
    while(1) {
        if ((game->light != 1) && (game->busy != 0)) {
            if ((game->cam)->poop_right == 1) {
                pthread_mutex_lock(&mutex);
                draw_other(poop_left, 11, 2, game);
                refresh();
                pthread_mutex_unlock(&mutex);
            }
            if ((game->cam)->poop_left == 1) {
                pthread_mutex_lock(&mutex);
                draw_other(poop_right, 11, 30, game);
                refresh();
                pthread_mutex_unlock(&mutex);
            }
            if ((game->cam)->attention == 1) {
                if (game->attention_selector == 1) {
                    if (game->current_option != 7) {
                        pthread_mutex_lock(&mutex);
                        mvaddstr(17, 28, "  ATTN  ");
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        game->attention_selector = 0;
                    }
                }
                /*switch(game->stage) {
                    case 1:
                        pthread_mutex_lock(&mutex);
                        draw_other(attention, 7, 25, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        break;
                    case 2:
                        break;
                    case 3:
                        pthread_mutex_lock(&mutex);
                        draw_other(attention, 3, 27, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        break;
                }*/
            }
            if (((game->cam)->sick != 1) && ((game->cam)->alive == 1)) {
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
            } else if (((game->cam)->sick == 1) && ((game->cam)->alive == 1)) {
                switch(game->stage) {
                    case 1:
                        pthread_mutex_lock(&mutex);
                        draw_sprite(animations->stage_sick, 10, 14, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        usleep(500000);
                        break;
                    case 2:
                        break;
                    case 3:
                        pthread_mutex_lock(&mutex);
                        draw_sprite(animations->dance_sick, 3, 8, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        usleep(500000);
                        break; 
                }
                //while((game->cam)->sick == 1);
           } else {
                switch(game->stage) {
                    case 1:
                        pthread_mutex_lock(&mutex);
                        draw_sprite(animations->stage_x, 10, 14, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        usleep(500000);
                        break;
                    case 2:
                        break;
                    case 3:
                        pthread_mutex_lock(&mutex);
                        draw_sprite(animations->dance_x, 3, 8, game);
                        refresh();
                        pthread_mutex_unlock(&mutex);
                        usleep(500000);
                        break; 
                }
                while(1);
            }
            if ((game->cam)->sick == 1) {
                hunger_mod = 60;
                happy_mod = 32;
                sick_mod = 100;
            } else if (game->stage == 1) {
                hunger_mod = 20;
                happy_mod = 20;
                sick_mod = 60;
            } else if (game->stage == 0) {
                continue;
            } else {
                hunger_mod = 80;
                happy_mod = 80;
                sick_mod = 200;
            }
            random = rand() % hunger_mod;
            if (random == 1) {
                pthread_mutex_lock(&mutex);
                decrement_hunger(game, 1);
                pthread_mutex_unlock(&mutex);
            }
            random = rand() % happy_mod;
            if (random == 1) {
                pthread_mutex_lock(&mutex);
                decrement_happy(game, 1);
                pthread_mutex_unlock(&mutex);
            }
            random = rand() % sick_mod;
            if (random == 1) {
                pthread_mutex_lock(&mutex);
                (game->cam)->sick = 1;
                pthread_mutex_unlock(&mutex);
            }
            random = rand() % 100;
            if (((game->cam)->hunger == 0) || ((game->cam)->happy == 0) || (random == 1)) {
                (game->cam)->attention = 1;
                game->attention_selector = 1;
                // wants_attention(game, &mutex);
            }
        }
    }
    pthread_exit(NULL);
}

void *growth(void *vgame) {
    Game *game = (Game *) vgame; 
    int stage = 0;
    int sick = 0;
    int hunger = 0;
    while(1) {
        usleep(1);
        stage++;
        if (stage == 2000000) {
            pthread_mutex_lock(&mutex);
            game->stage++;
            pthread_mutex_unlock(&mutex);
        } else if (stage == 4000000) {
            pthread_mutex_lock(&mutex);
            game->stage = 3;
            pthread_mutex_unlock(&mutex);
        }
        if ((game->cam)->sick == 1) {
            sick++;
        } else {
            sick = 0;
        }
        if ((game->cam)->hunger == 0) {
            hunger++;
        } else {
            hunger = 0;
        }
        if ((sick == 30000000) || (hunger == 30000000)) {
            pthread_mutex_lock(&mutex);
            (game->cam)->alive = 0;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_exit(NULL);
}

void *sick_check(void *vgame) {
    Game *game = (Game *) vgame; 
    clock_t start;
    while(1) {
        if ((game->cam)->sick == 1) {
            start = clock();
            while(clock() < start + 60000000) {
                if ((game->cam)->sick == 0) {
                    break;
                }
            }
            if ((game->cam)->sick == 1) {
                pthread_mutex_lock(&mutex);
                (game->cam)->alive = 0;
                pthread_mutex_unlock(&mutex);
            }
        }
        usleep(20000000);
    }
}

void create_threads(Game *game) {
    pthread_t threads[10];
    void* ret;
    pthread_create(&threads[0], NULL, wait_for_input, (void *) game);
    pthread_create(&threads[1], NULL, animation, (void *) game);
    pthread_create(&threads[2], NULL, growth, (void *) game);
    // pthread_create(&threads[3], NULL, sick_check, (void *) game);
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
    game->animations = malloc(sizeof(Animations));
    game->animations = init_animations();
    (game->cam)->happy = 0;
    (game->cam)->hunger = 0;
    (game->cam)->weight = 5;
    (game->cam)->age = 0;
    (game->cam)->sick = 0;
    (game->cam)->alive = 1;
    (game->cam)->poop_left = 0;
    (game->cam)->poop_right = 0;
    (game->cam)->attention = 0;
    (game->cam)->attention = 0;
    game->current_option = 0;
    game->attention_selector = 0;
    srand(time(NULL));
    init_screen(game);
    signal(SIGINT, destroy_signal);
    keypad(stdscr, TRUE);
    create_threads(game);
    destroy_game();
    return EXIT_SUCCESS;
}
