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
build done. The way i used to build things is by including
header to the corresponding source file. So I'm about to 
  accomplish the same in this project, but here I'm going to
include all of the source files
*/


#include "snake_game_update.c"
#include "snake_logic.c"
#include "snake_map.c"

#if defined(GUI_ENABLED)
#undef GUI_ENABLED
#endif /*defined(GUI_ENABLED)*/


#if defined(GUI_ENABLED)
#include "snake_renderer_raylib.c"
#else 
#include "snake_renderer_console_win.c"
#endif /*GUI_ENABLED*/


#endif //SNAKE_GAME_H
