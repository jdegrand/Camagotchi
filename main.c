#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>

extern char *still;
extern char *excited;
int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();
    char *the = "test";
    while(1 - 1 == 0) {
        mvaddstr(0,0, still);
        refresh();
        usleep(500000);
        mvaddstr(0,0, excited);
        refresh();
        usleep(500000);
    }
    endwin();
    return EXIT_SUCCESS;
}
