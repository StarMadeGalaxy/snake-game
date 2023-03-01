#include "snake_game.hpp"

#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>



int main(int arg_count, char* arg_array[])
{
    (void)arg_count;
    (void)arg_array;

    IPlatformAPI platform_api;

    std::unique_ptr<Map> game_map = std::make_unique<Map>(platform_api.screen_height_, 
                                                          platform_api.screen_width_);
    std::unique_ptr<Snake> snake = std::make_unique<Snake>(platform_api.screen_width_ / 2,
                                                           platform_api.screen_height_ / 2);

    GameInput game_input;
    while (snake->state() == SnakeState::Alive && platform_api.platform_active)
    {
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_W))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_W)] = GameKeyState::BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_A))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_A)] = GameKeyState::BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_S))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_S)] = GameKeyState::BUTTON_UP;
        }
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_D))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_D)] = GameKeyState::BUTTON_UP;
        }
#if defined(DEBUG_MODE)
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_SPACE))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_SPACE)] = GameKeyState::BUTTON_UP;
        }
#endif // defined(DEBUG_MODE)
        if (platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_ESC))
        {
            platform_api.platform_active = false;
        }
        
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_W))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_W)] = GameKeyState::BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_A))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_A)] = GameKeyState::BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_S))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_S)] = GameKeyState::BUTTON_DOWN;
        }
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_D))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_D)] = GameKeyState::BUTTON_DOWN;
        }
#if defined(DEBUG_MODE)
        if (!platform_api.is_key_pressed(InputKeyboardKeys::KEYBOARD_SPACE))
        {
            game_input.keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_SPACE)] = GameKeyState::BUTTON_DOWN;
        }
#endif // defined(DEBUG_MODE)
        game_render_update(&platform_api, &game_input, snake.get(), game_map.get());
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return EXIT_SUCCESS;
}