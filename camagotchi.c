///
/// FILENAME: camagotchi.c
#include "camagotchi.h"
/// DESCRIPTION: the implementation of the camagotchi
/// CONTRIBUTORS: Justin Sostre, Joe DeGrand
///

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "camagotchi.h"
#include "modes.h"
#include "game.h"

void change_mode(Game *game, pthread_mutex_t mutex) {
    switch(game->current_option) {
        case 0:
            feed(game, mutex);
            break;
        case 1:
            feed(game, mutex);
            break;
        case 2:
            play(game, mutex);
            break;
        case 3:
            break;
            feed(game, mutex);
        case 4:
            feed(game, mutex);
            break;
        case 5:
            feed(game, mutex);
            break;
        case 6:
            feed(game, mutex);
            break;
        case 7:
            feed(game, mutex);
            break;
    }
}

static void refuse_eat(Camagotchi *camagotchi) {
    //beep(camagotchi);
    // animation for being upset
    camagotchi->happiness -= 1;
}

int eat(Camagotchi *camagotchi, int foodtype) {

    if (foodtype == SNACK && camagotchi->hunger < 6) { // refuse to eat a snack
        refuse_eat(camagotchi);
        return -1;
    }
    else if (foodtype == MEAL && camagotchi->hunger < 20) { // refuse to eat
        refuse_eat(camagotchi);
        return -2;
    }

    // eating animation
    int feeds = 15*foodtype + 5;
    // removes 5 from hunger or 20 depending on foodtype 
    camagotchi->hunger =- feeds;

    return feeds;
} 



int die(Camagotchi *camagotchi) {

    
}
