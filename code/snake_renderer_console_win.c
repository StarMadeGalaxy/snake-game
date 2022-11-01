#include "snake_renderer_console_win.h"


RCW_API function WinConsoleRenderer* console_renderer_alloc()
{
    WinConsoleRenderer* renderer = (WinConsoleRenderer*)malloc(sizeof(WinConsoleRenderer));
    return renderer;
}


RCW_API function void console_renderer_init(WinConsoleRenderer* renderer)
{
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor_hide(renderer);
}


RCW_API function void console_cursor_hide(WinConsoleRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


RCW_API function void console_cursor_begin_move(WinConsoleRenderer* renderer)
{
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(renderer->console_handler, position);
}


RCW_API function void console_render_frame(Map* map_frame)
{
    for (u16 y = 0; y < map_frame->height; y++)
    {
        for (u16 x = 0; x < map_frame->width; x++)
        {
            switch (get_map_chunk(map_frame, x, y)->type)
            {
                case Border:
                {
                    fputc(BORDER_CHAR, stdout);
                    break;
                }
                case Space:
                {
                    fputc(SPACE_CHAR, stdout);
                    break;
                }
                case Head:
                {
                    fputc(HEAD_CHAR, stdout);
                    break;
                }
                case Body:
                {
                    fputc(BODY_CHAR, stdout);
                    break;
                }
                case Food:
                {
                    fputc(FOOD_CHAR, stdout);
                    break;
                }
                default:
                {
                    fputc('?', stdout);
                    break;
                }
            }
        }
        fputc('\n', stdout);
    }
} 