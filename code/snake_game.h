/* date = October 28th 2022 0:36 am */

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


/* 
#include "snake_types.h"
#include "snake_logic.h"
#include "snake_map.h"
#include "snake_renderer_console.h"
#include "snake_renderer_raylib.h"
 */


/* 
NOTE(Venci): 
I'm not sure if I should include all of the
headers files here. I'm just trying to get the unity 
build done. The way i used to build thing is by including
header to the corresponding source file. So I'm about to 
  accomplish the same in this project, but here I'm going to
include all of the source files
*/


#include "snake_logic.c"
#include "snake_map.c"
#include "snake_renderer_console.c"
#include "snake_renderer_raylib.c"


#endif //SNAKE_GAME_H
