/*
* FILE: border.h
* DESCRIPTION: Interface for the border surrounding the sprite
* CONTRIBUTORS: Joe DeGrand
*/

#ifndef BORDER_H_
#define BORDER_H_

#include "game.h"

char *outline();
void move_cursor(Game *game, int key);
#endif