///
/// FILENAME: camagotchi.c
/// DESCRIPTION: the implementation of the camagotchi
/// CONTRIBUTORS: Justin Sostre, Joe DeGrand
///

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "camagotchi.h"
#include "modes.h"

void wants_attention(Game *game, pthread_mutex_t *mutex) {
    
}

void change_mode(Game *game, pthread_mutex_t *mutex) {
    if ((game->cam)->alive == 0) {
        return;
    }
    if (game->current_option == 1) {
        lite(game, mutex);
    } else if ((game->light == 0) && (game->stage != 0)) {
        switch(game->current_option) {
            case 0:
                feed(game, mutex);
                break;
            case 1:
                lite(game, mutex);
                break;
            case 2:
                play(game, mutex);
                break;
            case 3:
                meds(game, mutex);
                break;
            case 4:
                duck(game, mutex);
                break;
            case 5:
                hlth(game, mutex);
                break;
            case 6:
                disc(game, mutex);
                break;
            case 7:
                attn(game, mutex);
                break;
        }
    }
}
