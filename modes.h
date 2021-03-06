#ifndef MODES_H_
#define MODES_H_

#include "camagotchi.h"
#include <pthread.h>

void feed(Game* game, pthread_mutex_t *mutex);
void lite(Game* game, pthread_mutex_t *mutex);
void play(Game* game, pthread_mutex_t *mutex);
void meds(Game* game, pthread_mutex_t *mutex);
void duck(Game* game, pthread_mutex_t *mutex);
void hlth(Game* game, pthread_mutex_t *mutex);
void disc(Game* game, pthread_mutex_t *mutex);
void attn(Game* game, pthread_mutex_t *mutex);
void increment_happy(Game *game, int amount);
void decrement_happy(Game *game, int amount);
void decrement_hunger(Game *game, int amount);
#endif
