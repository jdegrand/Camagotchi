///
/// FILENAME: camagotchi.h
/// DESCRIPTION: camagotchi interface
/// CONTRIBUTORS: Justin Sostre
///

#include <stdbool.h>

typedef struct Animations {
    char *dance1;
    char *dance2;
    char *dance3;
    
    char *eat1;
    char *eat2;
    char *eat3;

    char *medicine1;
    char *medicine2;
    char *medicine3;
};

typedef struct {
    char *name;
    struct animations;
    int age: 8;
    int discipline: 5;
    int happiness: 5;
    int health: 3;
    int sick: 2;
} Camagotchi;


int eat(Camagotchi *c, int foodtype);

int sleep(Camagotchi *c);

int discipline(Camagotchi *c);

int beep(Camagotchi *c);

int die(Camagotchi *c);

int medicine(Camagotchi *c);

