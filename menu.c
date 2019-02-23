#include <ncurses.h>
#include <stdio.h>

int main(void) {
    initscr()
    char choices[3][10] = {"New Game", "Load", "Exit"};
    char item[10];
    int ch, i;
    for(i = 0; i<3; i++) {
        if(i == 0)
            attron(A_STANDOUT);
        else
            attroff(A_STANDOUT);
        sprintf(item, choices[i]);
        mvprintw(i+1, 2, "%s", item);
    }
    i = 0;
    refresh();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    while((ch = getch()) != 'q') {
        sprintf(item, list[i]);
        mvprintw(i+1, 2, "%s", item);

        switch(ch) {
            case KEY_UP:
                i--;
                i = (i<0) ? 2 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i>2) ? 0 : i;
                break;
        }
        attron(A_STANDOUT);

        sprintf(item, list[i]);
        mvprintw(i+1, 2, "%s", item);
        attroff(A_STANDOUT);
    }
}
