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

void insert_options() {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    mvaddstr(1, 1, " FEED ");
    attroff(COLOR_PAIR(1));
    mvaddstr(1, 8, " LITE ");
    mvaddstr(1, 15, " PLAY ");
    mvaddstr(1, 22, " MEDS ");
    mvaddstr(17, 1, " DUCK ");
    mvaddstr(17, 8, " HLTH ");
    mvaddstr(17, 15, " DISC ");
    mvaddstr(17, 22, " ATTN ");
}

void edit_options(int cursor) {
    switch(cursor) {
        case 0:
            mvaddstr(1, 1, " FEED ");
            break;
        case 1:
            mvaddstr(1, 8, " LITE ");
            break;
        case 2:
            mvaddstr(1, 15, " PLAY ");
            break;
        case 3:
            mvaddstr(1, 22, " MEDS ");
            break;
        case 4:
            mvaddstr(17, 1, " DUCK ");
            break;
        case 5:
            mvaddstr(17, 8, " HLTH ");
            break;
        case 6:
            mvaddstr(17, 15, " DISC ");
            break;
        case 7:
            mvaddstr(17, 22, " ATTN ");
            break;
    }
}

void move_cursor(Game *game, int key) {
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    edit_options(game->current_option);
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
    edit_options(game->current_option);
    attroff(COLOR_PAIR(1));
}
