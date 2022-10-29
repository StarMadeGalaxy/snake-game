/* date = October 20th 2022 2:27 am */

#ifndef CONSOLE_LAYER_H
#define CONSOLE_LAYER_H

#define SNAKE_CONSOLE_VERSION

#ifdef _WIN32
#include <Windows.h>
#endif /*_WIN32*/

#include <conio.h>

/* 
NOTE(Venci):
There's probably another way without including snake_map.h.
Im wondering how could it be implemented in more effective 
and concise way. e.g. pushcommand, virual machine idk... 
 */
#include "snake_map.h"


static void console_cursor_hide(HANDLE* console_handler);
static void console_cursor_begin_move(HANDLE* console_handler);
static void console_render_frame(Map* map_frame);


typedef enum console_renderer_commands
{
    RENDER_FRAME
} console_renderer_commands;








#endif //CONSOLE_LAYER_H
