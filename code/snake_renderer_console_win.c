#include "snake_renderer_console_win.h"


static void console_renderer_init(ConsoleRenderer* renderer)
{
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
}


static void console_cursor_hide(ConsoleRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


static void console_cursor_begin_move(ConsoleRenderer* renderer)
{
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(renderer->console_handler, position);
}


static void console_render_frame(Map* map_frame)
{
    //console_cursor_hide();
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