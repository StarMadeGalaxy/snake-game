#include "snake_game.hpp"
#include "snake_map.hpp"

#include <ctime>
#include <chrono>
#include <thread>


int main(int arg_count, char* arg_array[])
{
    IPlatformAPI platform_api;
    
    Map* game_map = map_alloc(platform_api.screen_height_, 
                              platform_api.screen_width_);
    map_init(game_map);
    
    Snake* snake = snake_alloc();
    snake_init(snake, (u16)(platform_api.screen_width_ / 2), 
                      (u16)(platform_api.screen_height_ / 2), None);
    
    GameInput game_input;
    
    while (snake->state == Alive && platform_api.platform_active)
    {
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_W))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_W)] = BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_A))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_A)] = BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_S))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_S)] = BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_D))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_D)] = BUTTON_UP;
        }
#if defined(DEBUG_MODE)
        if (console_is_key_pressed((u32)VK_SPACE))
        {
            game_input.keyboard_keys[KEYBOARD_SPACE] = BUTTON_UP;
        }
#endif // defined(DEBUG_MODE)
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_ESC))
        {
            platform_api.platform_active = false;
        }
        
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_W))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_W)] = BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_A))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_A)] = BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_S))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_S)] = BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_D))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_D)] = BUTTON_DOWN;
        }
#if defined(DEBUG_MODE)
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_SPACE))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_SPACE)] = BUTTON_DOWN;
        }
#endif // defined(DEBUG_MODE)
        
        game_render_update(&platform_api, &game_input, snake, game_map);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    map_free(game_map);
    // Nullify snake for no reason?
    snake_free(&snake);

    return EXIT_SUCCESS;
}