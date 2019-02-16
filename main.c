#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>

typedef struct Tamagotchi {
  char *still_sprite;
  char *happy_sprite;
  int food; 
  int happiness; 
} Tamagotchi;

int main(int argc, char *argv[]) {
    return EXIT_SUCCESS;
}
