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


#if !defined(GUI_ENABLED) && !defined(UNICODE_ENABLED)
typedef char CONSOLE_FRAME_TYPE;
#elif !defined(GUI_ENABLED) && defined(UNICODE_ENABLED)
typedef wchar_t CONSOLE_FRAME_TYPE;
#endif /*defined(GUI_ENABLED)*/


#if defined(GUI_ENABLED)
# define RRL_API /*__declspec(dllexport)*/ /* (R)enderer (R)ay(L)ib  */
# define CURRENT_RENDERER RaylibRenderer
# include "snake_renderer_raylib.c"
#else
# define RCW_API /*__declspec(dllexport)*/ /* (R)enderer (C)onsole (W)in */
# define CURRENT_RENDERER WinConsoleRenderer
# include "snake_renderer_console_win.c"
#endif /*define(GUI_ENABLED)*/


#include "snake_game_update.c"
#include "snake_logic.c"
#include "snake_map.c"


#endif //SNAKE_GAME_H
