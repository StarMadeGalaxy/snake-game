/* date = October 20th 2022 2:27 am */

#ifndef SNAKE_RENDERER_CONSOLE_WIN
#define SNAKE_RENDERER_CONSOLE_WIN

#ifdef _WIN32
#include <Windows.h>
#endif /*_WIN32*/

#include <stdlib.h>
#include <conio.h>

#include "snake_map.h"
#include "snake_game_platform.h"
/* 
NOTE(Venci):
There's probably another way without including snake_map.h.
Im wondering how could it be implemented in more effective 
and concise way. e.g. pushcommand, virual machine idk... 
 *

// TODO(Venci): build renderer as dll in learning purposes
// #define RCW_API /*__declspec(dllexport)*/

/*
NOTE(Venci): 
I'm having a problem with designig this piece of code.
1) Im not sure what is the best practice to separate input layer
2) Im not sure how shouil implement renderer structure (C struct)
3) Where should I have the main loop?
4) And finally, should i even think about that for now, or I just should
keep working on the project without thinking about the design so hard???
Because it's definitely not the last project in my entire life.
*/


typedef struct WinConsoleRendererCommandsQueue
{
    void* commands_queue;
    
} WinConsoleRendererCommandsQueue;


typedef enum WinConsoleRendererCommand
{
    CLEAR_FRAME,
    RENDER_FRAME,
    
    RENDERER_COMMAND_COUNT
} WinConsoleRendererCommand;


typedef struct WinConsoleSize
{
    u16 height;
    u16 width;
} WinConsoleSize;


typedef struct WinConsoleRenderer
{
    WinConsoleRendererCommand commands;
    WinConsoleSize size; 
    void* data;
    HANDLE console_handler;
    DWORD bytes_written_last_frame;
} WinConsoleRenderer;


RCW_API internal u16 console_is_key_pressed(u32 virtual_key_code);
RCW_API internal void console_cursor_hide(WinConsoleRenderer* renderer);
RCW_API internal void console_cursor_begin_move(WinConsoleRenderer* renderer);
RCW_API internal void console_render_frame(WinConsoleRenderer* renderer);
RCW_API internal void console_renderer_destroy(WinConsoleRenderer* renderer);
RCW_API internal WinConsoleRenderer* console_renderer_create(u16 screen_height,
                                                             u16 screen_width);


#endif /*SNAKE_RENDERER_CONSOLE_WIN*/
