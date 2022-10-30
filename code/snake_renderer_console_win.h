/* date = October 20th 2022 2:27 am */

#ifndef SNAKE_RENDERER_CONSOLE_WIN
#define SNAKE_RENDERER_CONSOLE_WIN

#define SNAKE_CONSOLE_VERSION

#ifdef _WIN32
#include <Windows.h>
#endif /*_WIN32*/

#include <stdlib.h>
#include <conio.h>

/* 
NOTE(Venci):
There's probably another way without including snake_map.h.
Im wondering how could it be implemented in more effective 
and concise way. e.g. pushcommand, virual machine idk... 
 */
#include "snake_map.h"


typedef struct WinConsoleRenderer
{
    HANDLE* console_handler;
    /*void* data;*/
} WinConsoleRenderer;


static void console_cursor_hide(WinConsoleRenderer* renderer);
static void console_cursor_begin_move(WinConsoleRenderer* renderer);
static void console_render_frame(Map* map_frame);
static void console_renderer_init(WinConsoleRenderer* renderer);
static WinConsoleRenderer* console_renderer_alloc();

typedef enum console_renderer_commands
{
    RENDER_FRAME
} console_renderer_commands;








#endif /*SNAKE_RENDERER_CONSOLE_WIN*/
