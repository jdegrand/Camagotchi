///
/// FILENAME: camagotchi.h
/// DESCRIPTION: camagotchi interface
/// CONTRIBUTORS: Justin Sostre
///

#ifndef CAMAGOTCHI_H_
#define CAMAGOTCHI_H_

#include <stdbool.h>
#include <pthread.h>
#include "game.h"

#define SNACK 0
#define MEAL 0

typedef struct {
    char *egg1;
    char *egg2;
    char *egg3;
    
    char *egg_rotate1;
    char *egg_rotate2;
    char *egg_rotate3;
    char *egg_rotate4;
    char *egg_rotate5;
    
    char *dance1;
    char *dance2;
    char *dance3;
    
    char *eat1;
    char *eat2;
    char *eat3;

    char *medicine1;
    char *medicine2;
    char *medicine3;
} Animations;

typedef struct {
    char *name;
    Animations animations;
    int age: 8;
    int discipline: 5;
    int happiness: 5;
    int hunger: 5;
    int health: 3;
    int sick: 2;
} Camagotchi;


void change_mode(Game *game, pthread_mutex_t mutex);

int eat(Camagotchi *camagotchi, int foodtype);

int sleepc(Camagotchi *camagotchi);

int discipline(Camagotchi *camagotchi);

int beep_sound(Camagotchi *camagotchi);

int die(Camagotchi *camagotchi);

int medicine(Camagotchi *camagotchi);

#endif
