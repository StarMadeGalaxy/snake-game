#include "snake_renderer_console.h"


internal u16 console_is_key_pressed(u32 virtual_key_code)
{
#if defined(_WIN32)
    return (GetAsyncKeyState(virtual_key_code) & MSB(u16));
#endif
}


internal void console_renderer_destroy(ConsoleRenderer* renderer)
{
    free(renderer->frame_data);
    free(renderer);
}


internal ConsoleRenderer* console_renderer_create(u16 screen_height,
                                                  u16 screen_width)
{
    ConsoleRenderer* renderer = (ConsoleRenderer*)malloc(sizeof(ConsoleRenderer));
    
    size_t data_size = (size_t)screen_height * (size_t)screen_width;
    
    renderer->frame_data = (CONSOLE_FRAME_TYPE*)malloc(data_size * sizeof(CONSOLE_FRAME_TYPE));
    renderer->size.height = screen_height;
    renderer->size.width = screen_width;
#if defined(_WIN32) 
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    console_cursor_hide(renderer);
#endif // defined(_WIN_32)
    
    return renderer;
}


internal void console_cursor_hide(ConsoleRenderer* renderer)
{
#if defined(_WIN32)
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
#endif // defined(_WIN32)
}


#define MAKE_MAP
#define MAKE_SNAKE
internal void console_make_frame(ConsoleRenderer* renderer, 
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
                case Food:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = FOOD_CHAR;
                    break;
                }
                case Border:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BORDER_CHAR;
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
        u32 index = snake->head->coord.y * renderer->size.width + snake->head->coord.x;
        switch (snake->head->type)
        {
            case Body:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BODY_CHAR;
                break;
            }
            case Head:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = HEAD_CHAR;
                break;
            }
            case Tail:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = TAIL_CHAR;
                break;
            }
        }
        snake->head = snake->head->next;
    }
    snake->head = temp_chunk;
#endif // defined(MAKE_SNAKE)
}


internal void console_cursor_begin_move(ConsoleRenderer* renderer)
{
#if defined(_WIN32)
    COORD position = { 0, 0 };
    SetConsoleCursorPosition(renderer->console_handler, position);
#endif // defined(_WIN32)
}


internal void console_render_frame(ConsoleRenderer* renderer)
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
} 
