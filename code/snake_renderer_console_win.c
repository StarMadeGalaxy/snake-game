#include "snake_renderer_console_win.h"


internal u16 console_is_key_pressed(u32 virtual_key_code)
{
    return (GetAsyncKeyState(virtual_key_code) & MSB(u16));
}


internal void console_renderer_destroy(WinConsoleRenderer* renderer)
{
    free(renderer->frame_data);
    free(renderer);
}


internal WinConsoleRenderer* console_renderer_create(u16 screen_height,
                                                     u16 screen_width)
{
    WinConsoleRenderer* renderer = (WinConsoleRenderer*)malloc(sizeof(WinConsoleRenderer));
    
    size_t new_line_number = (size_t)screen_height;
    size_t data_size = (size_t)screen_height * (size_t)screen_width + new_line_number;
    
    renderer->frame_data = (CONSOLE_FRAME_TYPE*)malloc(data_size * sizeof(CONSOLE_FRAME_TYPE));
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    renderer->size.height = screen_height;
    renderer->size.width = screen_width + 1;
    
    console_cursor_hide(renderer);
    return renderer;
}

#if 0 
internal void console_renderer_init(WinConsoleRenderer* renderer,
                                    u16 screen_height,
                                    u16 screen_width)
{
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    renderer->size.height = screen_height;
    renderer->size.width = screen_width;
    console_cursor_hide(renderer);
}
#endif 

internal void console_cursor_hide(WinConsoleRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


internal void console_make_frame(WinConsoleRenderer* renderer, 
                                 Snake* snake, 
                                 Map* game_map)
{
    // NOTE(Venci): renderer size coord mapped to game_map
    
    u16 x;
    u16 y;
    
    for (y = 0; y < game_map->height; y++) 
    {
        for (x = 0; x < game_map->width; x++) 
        {
            u32 index = y * renderer->size.width + x;
            
            switch(get_map_chunk(game_map, x, y)->type) 
            {
                case Space:
                {
                    renderer->frame_data[index] = (CONSOLE_FRAME_TYPE)SPACE_CHAR;
                    break;
                }
                case Border:
                {
                    renderer->frame_data[index] = (CONSOLE_FRAME_TYPE)BORDER_CHAR;
                    break;
                }
            }
        }
        renderer->frame_data[y * renderer->size.width + x] = '\n';
    }
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




internal void console_render_frame(WinConsoleRenderer* renderer)
{
    COORD screen_buffer_first_cell;
    screen_buffer_first_cell.X = 0;
    screen_buffer_first_cell.Y = 0;
    DWORD screen_buffer_length = renderer->size.height * renderer->size.width;
    
    WriteConsoleOutputCharacterA(renderer->console_handler,
                                 renderer->frame_data,
                                 screen_buffer_length,
                                 screen_buffer_first_cell,
                                 &renderer->bytes_written_last_frame);
#if 0
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
#endif 
} 
