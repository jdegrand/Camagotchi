///
/// FILENAME: animations.h
/// DESCRIPTION: Interface for animations
/// CONTRIBUTORS: Joe DeGrand
///


#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#include "./camagotchi.h"

Animations *init_animations();
void draw_other(char *to_print, int row, int col, Game *game);
void draw_sprite(char *to_print, int row, int col, Game *game);

#endif
