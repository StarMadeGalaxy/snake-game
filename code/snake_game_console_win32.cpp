#include "snake_game_platform.hpp" // API to implement

#include "snake_game_console_win32.hpp"
#include "snake_types.hpp"
#include "snake_map.hpp"

#include <memory>
#include <windows.h>
#include <stdio.h>


namespace settings
{
    constexpr std::size_t height = 15; 
    constexpr std::size_t width = 25;
}


u16 console_is_key_pressed(i32 virtual_key_code)
{
    return (GetAsyncKeyState(virtual_key_code) & MSB(u16));
}


void console_renderer_destroy(GameRenderer* renderer)
{
    free(renderer->frame_data);
}


void console_cursor_hide(GameRenderer* renderer)
{
    CONSOLE_CURSOR_INFO cc_info;
    GetConsoleCursorInfo(renderer->console_handler, &cc_info);
    cc_info.bVisible = 0;
    SetConsoleCursorInfo(renderer->console_handler, &cc_info);
}


#define MAKE_MAP
#define MAKE_SNAKE
void console_make_frame(GameRenderer* renderer, Snake* snake, Map* game_map)
{
    // NOTE(Venci): filling renderer data with map
    for (u16 y = 0; y < game_map->height(); y++) 
    {
        for (u16 x = 0; x < game_map->width(); x++) 
        {
            std::size_t index = y * renderer->size.width + x;
            switch(game_map->get_map_chunk(x, y)->type) 
            {
                case ChunkType::Space:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = SPACE_CHAR;
                    break;
                }
                case ChunkType::Food:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = FOOD_CHAR;
                    break;
                }
                case ChunkType::Border:
                {
                    ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BORDER_CHAR;
                    break;
                }
                case ChunkType::Body: { break; }
                case ChunkType::Head: { break; }
                case ChunkType::Tail: { break; }
            }
        }
    }
    
    // NOTE(Venci): filling renderer data with snake
    SnakeChunk* temp_chunk = snake->head();
    while (snake->head() != NULL)
    {
        std::size_t index = snake->head()->coord.y * renderer->size.width + snake->head()->coord.x;
        switch (snake->head()->type)
        {
            case ChunkType::Body:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = BODY_CHAR;
                break;
            }
            case ChunkType::Head:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = HEAD_CHAR;
                break;
            }
            case ChunkType::Tail:
            {
                ((CONSOLE_FRAME_TYPE*)renderer->frame_data)[index] = TAIL_CHAR;
                break;
            }
            case ChunkType::Border: { break; }
            case ChunkType::Space: { break; }
            case ChunkType::Food: { break; }
        }
        snake->head_next();
    }
    snake->set_head(temp_chunk);
}


void console_cursor_begin_move(GameRenderer* renderer)
{
    SetConsoleCursorPosition(renderer->console_handler, renderer->cbsi.dwCursorPosition);
}


void console_render_frame(GameRenderer* renderer)
{
    for (u16 y = 0; y < renderer->size.height; y++)
    {
        for (u16 x = 0; x < renderer->size.width; x++)
        {
            std::size_t index = y * renderer->size.width + x;
            fputc(((char*)renderer->frame_data)[index], stdout);
        }
        fputc('\n', stdout);
    }
} 

//
// API Implementation
//

void IPlatformAPI::renderer_create(void)
{
    renderer = std::make_unique<GameRenderer>();
    
    std::size_t data_size = screen_height_ * screen_width_;
    
    renderer->frame_data = (CONSOLE_FRAME_TYPE*)malloc(data_size * sizeof(CONSOLE_FRAME_TYPE));
    renderer->size.height = screen_height_;
    renderer->size.width = screen_width_;
    renderer->console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(renderer->console_handler, &cbsi);
    
    renderer->cbsi.dwCursorPosition.X = 0;
    renderer->cbsi.dwCursorPosition.Y += 1;
    
    console_cursor_hide(renderer.get());
}


void IPlatformAPI::renderer_destroy(void)
{
    free(renderer->frame_data);
}


void IPlatformAPI::render_frame(Snake* snake, Map* map)
{
    console_cursor_begin_move(renderer.get());
    console_make_frame(renderer.get(), snake, map);
    console_render_frame(renderer.get());
}


bool IPlatformAPI::is_key_pressed(InputKeyboardKeys key)
{
    u16 virtual_key_code{};

    switch (key)
    {
    case InputKeyboardKeys::KEYBOARD_W:
        virtual_key_code = VK_W;
        break;    
    case InputKeyboardKeys::KEYBOARD_A:    
        virtual_key_code = VK_A;
        break;
    case InputKeyboardKeys::KEYBOARD_S:    
        virtual_key_code = VK_S;
        break;
    case InputKeyboardKeys::KEYBOARD_D:    
        virtual_key_code = VK_D;
        break;
    case InputKeyboardKeys::KEYBOARD_ESC:
        virtual_key_code = VK_ESCAPE;
        break;
    case InputKeyboardKeys::KEYBOARD_SPACE:
        virtual_key_code = VK_SPACE;
        break;
    case InputKeyboardKeys::KEYBOARD_KEYS_COUNT: { break; }
    }

    return static_cast<bool>(GetAsyncKeyState(virtual_key_code) & MSB(u16));
}


IPlatformAPI::IPlatformAPI() :
        screen_height_(settings::height), screen_width_(settings::width) 
{
    platform_active = true;
    renderer_create();
}


IPlatformAPI::~IPlatformAPI(void)
{
    renderer_destroy();
}