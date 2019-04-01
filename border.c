#include <stdlib.h>

#include "border.h"
#include "game.h"
#include <curses.h>

char *outline() {
    char *main_outline = "\
|---------------------------|\n\
|      |      |      |      |\n\
|---------------------------|\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|                           |\n\
|---------------------------|\n\
|      |      |      |      |\n\
|---------------------------|\n\0";
        return main_outline;
}

void move_cursor(Game *game, int key) {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    switch(game->current_option) {
        case 0:
            mvaddstr(1, 1, "      ");
            break;
        case 1:
            mvaddstr(1, 8, "      ");
            break;
        case 2:
            mvaddstr(1, 15, "      ");
            break;
        case 3:
            mvaddstr(1, 22, "      ");
            break;
        case 4:
            mvaddstr(17, 1, "      ");
            break;
        case 5:
            mvaddstr(17, 8, "      ");
            break;
        case 6:
            mvaddstr(17, 15, "      ");
            break;
        case 7:
            mvaddstr(17, 22, "      ");
            break;
    }
    attron(COLOR_PAIR(1));
    if (key == KEY_LEFT) {
        game->current_option--;
        if (game->current_option == -1) {
            game->current_option = 7;
        }
    } else if (key == KEY_RIGHT) {
        game->current_option++;
        if (game->current_option == 8) {
            game->current_option = 0;
        }
    }
    switch(game->current_option) {
        case 0:
            mvaddstr(1, 1, "      ");
            break;
        case 1:
            mvaddstr(1, 8, "      ");
            break;
        case 2:
            mvaddstr(1, 15, "      ");
            break;
        case 3:
            mvaddstr(1, 22, "      ");
            break;
        case 4:
            mvaddstr(17, 1, "      ");
            break;
        case 5:
            mvaddstr(17, 8, "      ");
            break;
        case 6:
            mvaddstr(17, 15, "      ");
            break;
        case 7:
            mvaddstr(17, 22, "      ");
            break;
    }
    attroff(COLOR_PAIR(1));
}
