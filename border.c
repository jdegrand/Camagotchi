#include <stdlib.h>

#include "border.h"
#include "camagotchi.h"
#include <curses.h>

char *outline() {
    char *main_outline = "\
|-----------------------------------|\n\
|        |        |        |        |\n\
|-----------------------------------|\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|                                   |\n\
|-----------------------------------|\n\
|        |        |        |        |\n\
|-----------------------------------|\n\0";
        return main_outline;
}

void insert_options() {
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    // init_color(COLOR_TAN, 217, 220, 118);
    //init_pair(1, COLOR_TAN, COLOR_TAN);
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvaddstr(1, 1, "  FEED  ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    mvaddstr(1, 10, "  LITE ");
    mvaddstr(1, 19, "  PLAY  ");
    mvaddstr(1, 28, "  MEDS  ");
    mvaddstr(17, 1, "  DUCK  ");
    mvaddstr(17, 10, "  HLTH  ");
    mvaddstr(17, 19, "  DISC  ");
    mvaddstr(17, 28, "  ATTN  ");
}

void edit_options(int cursor) {
    switch(cursor) {
        case 0:
            mvaddstr(1, 1, "  FEED  ");
            break;
        case 1:
            mvaddstr(1, 10, "  LITE  ");
            break;
        case 2:
            mvaddstr(1, 19, "  PLAY  ");
            break;
        case 3:
            mvaddstr(1, 28, "  MEDS  ");
            break;
        case 4:
            mvaddstr(17, 1, "  DUCK  ");
            break;
        case 5:
            mvaddstr(17, 10, "  HLTH  ");
            break;
        case 6:
            mvaddstr(17, 19, "  DISC  ");
            break;
        case 7:
            mvaddstr(17, 28, "  ATTN  ");
            break;
    }
}

void move_cursor(Game *game, int key) {
    // init_pair(1, COLOR_BLACK, COLOR_WHITE);
    edit_options(game->current_option);
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    if (key == KEY_LEFT) {
        game->current_option--;
        if (game->current_option == -1) {
            game->current_option = 7;
        }
    } else if ((key == KEY_RIGHT) || (key == 'b')) {
        game->current_option++;
        if (game->current_option == 8) {
            game->current_option = 0;
        }
    }
    edit_options(game->current_option);
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
}
