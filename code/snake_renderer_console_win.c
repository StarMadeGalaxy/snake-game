#include "snake_renderer_console_win.h"


internal u16 console_is_key_pressed(u32 virtual_key_code)
{
    return (GetAsyncKeyState(virtual_key_code) & MSB(u16));
}


internal WinConsoleRenderer* console_renderer_alloc()
{
    WinConsoleRenderer* renderer = (WinConsoleRenderer*)malloc(sizeof(WinConsoleRenderer));
    return renderer;
}


internal void console_renderer_init(WinConsoleRenderer* renderer,
                                    u16 screen_height,
                                    u16 screen_width)
{
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    renderer->size.height = screen_height;
    renderer->size.width = screen_width;
    console_cursor_hide(renderer);
}


internal void console_cursor_hide(WinConsoleRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


internal void console_cursor_begin_move(WinConsoleRenderer* renderer)
{
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(renderer->console_handler, position);
}



#if 0
// Display Map
for (int nx = 0; nx < nMapWidth; nx++)
{
    for (int ny = 0; ny < nMapWidth; ny++)
    {
        screen[(ny+1)*nScreenWidth + nx] = map[ny * nMapWidth + nx];
    }
    screen[((int)fPlayerX+1) * nScreenWidth + (int)fPlayerY] = 'P';
}

// Display Frame
screen[nScreenWidth * nScreenHeight - 1] = '\0';
WriteConsoleOutputCharacterA(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
#endif


#define RENDER_THROUGH_RENDERER
#define RENDER_THROUGH_MAP
#undef RENDER_THROUGH_MAP

internal void console_render_frame(WinConsoleRenderer* renderer/*Map* map_frame*/)
{
#if defined(RENDER_THROUGH_RENDERER)
    
#endif /*defined(RENDER_THROUGH_RENDERER)*/
    COORD screen_buffer_first_cell;
    screen_buffer_first_cell.X = 0;
    screen_buffer_first_cell.Y = 0;
    DWORD screen_buffer_length = renderer->size.height * renderer->size.width;
    
    WriteConsoleOutputCharacterA(renderer->console_handler,
                                 renderer->data,
                                 screen_buffer_length,
                                 screen_buffer_first_cell,
                                 &renderer->BytesWrittenLastFrame);
    
#if defined(RENDER_THROUGH_MAP)
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
#endif /*defined(RENDER_THROUGH_MAP)*/
} 