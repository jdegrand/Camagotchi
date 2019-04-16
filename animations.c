#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <stdio.h>

#include "animations.h"
#include "camagotchi.h"

Animations *init_animations() {
    Animations *animations = malloc(sizeof(Animations));
    animations->egg1 = "\
  *****  \n\
 *  *  * \n\
 **  * * \n\
 * *   * \n\
  *****  \0";
    animations->egg2 = "\
   *****  \n\
  *  *  * \n\
  **  * * \n\
 * *   *  \n\
  *****\0";
    animations->egg3 = "\
 *****  \n\
*  *  * \n\
**  *  * \n\
 * *   *  \n\
  *****\0";
    animations->egg_rotate1 = "\
  *****  \n\
 * *   * \n\
 *  *  * \n\
 *   * * \n\
  *****  \0";
    animations->egg_rotate2 = "\
  *****  \n\
 *  *  * \n\
 *   * * \n\
 *    ** \n\
  *****  \0";
    animations->egg_rotate3 = "\
  *****  \n\
 *   * * \n\
 *    ** \n\
 **    * \n\
  *****  \0";
    animations->egg_rotate4 = "\
  *****  \n\
 *    ** \n\
 **    * \n\
 * *   * \n\
  *****  \0";
    animations->egg_rotate5 = "\
  *****  \n\
 **    * \n\
 * *   * \n\
 *  *  * \n\
  *****  \0";
    animations->stage1 = "\
           \n\
   ****    \n\
  *O**O*   \n\
  ******   \n\
   ****    \0";
    animations->stage2 = "\
           \n\
           \n\
   ****    \n\
  *O**O*   \n\
********** \0";
    animations->stage3 = "\
   ****    \n\
  *O**O*   \n\
  ******   \n\
  ******   \n\
   ****    \0";
    animations->stage4 = "\
   ****    \n\
  *O**O*   \n\
  ******   \n\
   ****    \n\
           \0";
    animations->stage5 = "\
 **** \n\
*O**O*\n\
******\n\
 **** \0";
    animations->stage_sick = "\
        \n\
        \n\
   **** \n\
  *X**X*\n\
********** \0";
    animations->dance1 ="\
     *********\n\
    *         *\n\
********  O    *\n\
*      *       *\n\
********       *\n\
*     *        *      \n\
*******        * **   \n\
   *     * *   ** *   \n\
   *      *    * *    \n\
   *           **     \n\
   *           *      \n\
    ***********\n\
   ****      ***\n\0";

    animations->dance2 = "\
                \n\
     ********* \n\
    *         * \n\
********  O    *\n\
*      *       *\n\
********       *\n\
*     *        *      \n\
*******   *    *   ** \n\
   *     * *   ****  *\n\
   *           *  *** \n\
   *           ***    \n\
    ***********\n\
   ***       ***\n\0";

    animations->dance3 = NULL;
    animations->dance_sick ="\
     *********\n\
    *         *\n\
********  X    *\n\
*      *       *\n\
********       *\n\
*     *        *      \n\
*******        * **   \n\
   *     * *   ** *   \n\
   *      *    * *    \n\
   *           **     \n\
   *           *      \n\
    ***********\n\
   ****      ***\n\0";
    animations->eat1 ="\
        **       **\n\
       *  *     *  *\n\
        *   *  *  *\n\
          *  **  *\n\
       *****     ******\n\
     *      *   *      *\n\
    *                U   *\n\
   *                    *\n\
   *                   *\n\
   *      *      ******\n\
   *     * *    * *\n\
   *           **\n\
   *         *\n\
    ***********\n\
   ****      ***\n\0";
    
    animations->eat2 ="\
           **  **\n\
          * *  * *\n\
          * *  * *\n\
          *  **  *\n\
       *****     ******\n\
     *    *      *      *\n\
    *                V   *\n\
   *                    *\n\
   *                   *\n\
   *      *      ******\n\
   *     * *    * *\n\
   *           **\n\
   *         *\n\
    ***********\n\
   ****      ***\n\0";
    animations->eat3 = NULL;
    animations->medicine1=NULL;
    animations->medicine2=NULL;
    animations->medicine3=NULL;
    return animations;
}


void draw_other(char *to_print, int row, int col) {
    char *tok;
    char *string = strdup(to_print);
    tok = strtok(string, "\n");
    while (tok != NULL) {
        mvaddstr(row, col, tok);
        tok = strtok(NULL, "\n");
        row++;
    }
}

void draw_sprite(char *to_print, int row, int col, Game *game) {
    if ((game->busy != 0) && (game->light != 1)) {
        char *tok;
        char *string = strdup(to_print);
        tok = strtok(string, "\n");
        while (tok != NULL) {
            mvaddstr(row, col, tok);
            tok = strtok(NULL, "\n");
            row++;
        }
    }
}
