#include <stdlib.h>

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
     *********\n\
    *         *\n\
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

