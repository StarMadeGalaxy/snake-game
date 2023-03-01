#if !defined(SNAKE_GAME_PLATFORM_H)
#define SNAKE_GAME_PLATFORM_H

#include <cstddef>
#include <iostream>

#include "snake_types.hpp"
#include "snake_logic.hpp"
#include "snake_map.hpp"


enum class InputKeyboardKeys
{
    KEYBOARD_SPACE,
    KEYBOARD_W,
    KEYBOARD_A,
    KEYBOARD_S,
    KEYBOARD_D,
    KEYBOARD_ESC,
    
    KEYBOARD_KEYS_COUNT
};


enum class GameKeyState
{
    BUTTON_DOWN,
    BUTTON_UP,
    
    BUTTON_STATES_COUNT
};


struct GameInput
{
    GameKeyState keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_KEYS_COUNT)];
};


struct GameRenderer;


class IPlatformAPI
{
public:
    std::size_t screen_height_;
    std::size_t screen_width_;

    GameRenderer* renderer;
    GameInput* input;

    bool platform_active;
public:
    IPlatformAPI();

    bool is_key_pressed(InputKeyboardKeys key);
    void renderer_destroy(void);
    void render_frame(Snake* snake, Map* map);

    ~IPlatformAPI(void);
private:
    void renderer_create(void);
};


void game_render_update(IPlatformAPI* game_platform, 
                                 GameInput* input, Snake* snake, 
                                 Map* game_map)          
{
#if defined(DEBUG_MODE)
    if (input->keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_SPACE)] == GameKeyState::BUTTON_UP)
    {
        snake->head()->direction = ChunkDirection::None;
    }
#endif // defined(DEBUG)

    if ((input->keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_W)] == GameKeyState::BUTTON_UP) && 
        snake->head()->direction != ChunkDirection::Down) 
    {
        snake->head()->direction = ChunkDirection::Up;
    }
    if ((input->keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_A)] == GameKeyState::BUTTON_UP) && 
        snake->head()->direction != ChunkDirection::Right)
    {
        snake->head()->direction = ChunkDirection::Left;
    }
    if ((input->keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_S)] == GameKeyState::BUTTON_UP) && 
        snake->head()->direction != ChunkDirection::Up)
    {
        snake->head()->direction = ChunkDirection::Down;
    }
    if ((input->keyboard_keys[INDEX(InputKeyboardKeys::KEYBOARD_D)] == GameKeyState::BUTTON_UP) && 
        snake->head()->direction != ChunkDirection::Left)
    {
        snake->head()->direction = ChunkDirection::Right;
    }
    if (snake->head()->direction != ChunkDirection::None)
    {
        snake->snake_move();
        snake->snake_rotate();
    }
    
    CollisionType snake_collision = snake->snake_collision_check(game_map);
    
    switch (snake_collision)
    {
        case CollisionType::BORDER_COLLISION:
        {
            snake->die();
            break;
        }
        case CollisionType::BODY_COLLISION:
        {
            snake->die();;
            break;
        }
        case CollisionType::FOOD_COLLISION:
        {
            game_map->food_chunk()->type = ChunkType::Space;
            snake->snake_grow(1);
            break;
        }
        case CollisionType::NONE_COLLISION: { break; }
    }
    
    // NOTE(Venci): temp solution
    if (game_map->food_chunk()->type != ChunkType::Food)
        (void)game_map->food_generate();

    game_platform->render_frame(snake, game_map);
}


#endif // !defined(SNAKE_GAME_PLATFORM_H)