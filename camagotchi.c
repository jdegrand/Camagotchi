///
/// FILENAME: camagotchi.c
/// DESCRIPTION: the implementation of the camagotchi
/// CONTRIBUTORS: Justin Sostre
///

#include <stdlib.h>
#include <stdio.h>
#include <camagotchi.h>


static void refuse_eat(Camagotchi *camagotchi) {
    beep(camagotchi);
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
    int feed = 15*foodtype + 5;
    // removes 5 from hunger or 20 depending on foodtype 
    camagotchi->hunger =- feed;

    return feed;
} 


int die(Camagotchi *camagotchi) {

    

}
