/*
* FILE: border.h
* DESCRIPTION: Interface for the border surrounding the sprite
* CONTRIBUTORS: Joe DeGrand
*/

#ifndef BORDER_H_
#define BORDER_H_

#include "camagotchi.h"

char *outline();
void insert_options();
void edit_options(int cursor);
void move_cursor(Game *game, int key);
#endif
