///
/// FILENAME: camagotchi.h
/// DESCRIPTION: camagotchi interface
/// CONTRIBUTORS: Justin Sostre
///

#ifndef CAMAGOTCHI_H_
#define CAMAGOTCHI_H_

#include <stdbool.h>
#include <pthread.h>

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

    char *stage1;
    char *stage2;
    char *stage3;
    char *stage4;
    char *stage5;
    char *stage_sick;

    char *dance1;
    char *dance2;
    char *dance3;
    char *dance_sick;

    char *eat1;
    char *eat2;
    char *eat3;

    char *medicine1;
    char *medicine2;
    char *medicine3;
} Animations;

typedef struct {
    char *name;
    int age;
    int discipline;
    int happiness;
    int happy;
    int hunger;
    int health;
    int sick;
    int weight;
    int poop_left;
    int poop_right;
} Camagotchi;

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
    int light;
    int busy;
    Camagotchi *cam;
    Animations *animations;
} Game;


void change_mode(Game *game, pthread_mutex_t *mutex);

int eat(Camagotchi *camagotchi, int foodtype);

int sleepc(Camagotchi *camagotchi);

int discipline(Camagotchi *camagotchi);

int beep_sound(Camagotchi *camagotchi);

int die(Camagotchi *camagotchi);

int medicine(Camagotchi *camagotchi);

#endif
