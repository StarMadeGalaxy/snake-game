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
    
    size_t data_size = (size_t)screen_height * (size_t)screen_width;
    
    renderer->frame_data = (CONSOLE_FRAME_TYPE*)malloc(data_size * sizeof(CONSOLE_FRAME_TYPE));
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    renderer->size.height = screen_height;
    renderer->size.width = screen_width;
    
    console_cursor_hide(renderer);
    return renderer;
}


internal void console_cursor_hide(WinConsoleRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


#define MAKE_MAP
#define MAKE_SNAKE
internal void console_make_frame(WinConsoleRenderer* renderer, 
                                 Snake* snake, 
                                 Map* game_map)
{
#if defined(MAKE_MAP)    // NOTE(Venci): filling renderer data with map
    for (u16 y = 0; y < game_map->height; y++) 
    {
        for (u16 x = 0; x < game_map->width; x++) 
        {
            u32 index = y * renderer->size.width + x;
            switch(get_map_chunk(game_map, x, y)->type) 
            {
                case Space:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = SPACE_CHAR;
                    break;
                }
                case Border:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = (CONSOLE_FRAME_TYPE)BORDER_CHAR;
                    break;
                }
            }
        }
    }
#endif // defined(MAKE_MAP)
#if defined(MAKE_SNAKE)    // NOTE(Venci): filling renderer data with snake
    SnakeChunk* temp_chunk = snake->head;
    while (snake->head != NULL)
    {
        u32 index = snake->head->y * renderer->size.width + snake->head->x;
        switch (snake->head->type)
        {
            case Body:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BODY_CHAR;
            }
            case Head:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = HEAD_CHAR;
            }
        }
        snake->head = snake->head->next;
    }
    snake->head = temp_chunk;
#endif // defined(MAKE_SNAKE)
}


internal void console_cursor_begin_move(WinConsoleRenderer* renderer)
{
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(renderer->console_handler, position);
}


internal void console_render_frame(WinConsoleRenderer* renderer)
{
    for (u16 y = 0; y < renderer->size.height; y++)
    {
        for (u16 x = 0; x < renderer->size.width; x++)
        {
            u32 index = y * renderer->size.width + x;
            fputc(((char*)renderer->frame_data)[index], stdout);
        }
        fputc('\n', stdout);
    }
#if defined(WINDOWS_SUCKS)
    COORD screen_buffer_first_cell;
    screen_buffer_first_cell.X = 0;
    screen_buffer_first_cell.Y = 0;
    DWORD screen_buffer_length = renderer->size.height * renderer->size.width;
    
    WriteConsoleOutputCharacterA(renderer->console_handler,
                                 renderer->frame_data,
                                 screen_buffer_length,
                                 screen_buffer_first_cell,
                                 &renderer->bytes_written_last_frame);
#endif // defined(WINDOWS_SUCKS)
} 
