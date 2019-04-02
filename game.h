#ifndef _GAME_H_
#define _GAME_H_

/*
 * Stages:
 * 0 - Egg
 * 1 - Baby
 * 2 - Child
 * 3 - Teen
*/
typedef struct Game {
    int x;
    int end;
    int flag;
    int current_option;
    int stage;
} Game;



#endif
