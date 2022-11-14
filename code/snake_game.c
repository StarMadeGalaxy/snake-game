#include "snake_game.h"
#include <Windows.h>
#include <time.h>


#pragma warning( disable : 4554 )

int main(int arg_count, char* arg_array[])
{
    srand((u32)time(NULL)); 
    
    const u16 screen_width = 25;
    
    const u16 screen_height = 15;
    
    Map* game_map = map_alloc(screen_height, screen_width);
    map_init(game_map);
    
    Snake* snake = snake_alloc();
    snake_init(snake, (u16)(screen_width / 2), (u16)(screen_height / 2), None);
    
#if !defined(GUI_ENABLED)
    WinConsoleRenderer* renderer = console_renderer_create(screen_height, screen_width);
#elif defined(GUI_ENABLED)
#endif // !defined(GUI_ENABLED)
    
    
    GameInput game_input;
    
    // NOTE(Venci): this entire file should GUI_ENABLED independent 
    for (;;)
    {
#if !defined(GUI_ENABLED)
        if (console_is_key_pressed((u32)VK_W))
        {
            game_input.keyboard_keys[KEYBOARD_W] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_A))
        {
            game_input.keyboard_keys[KEYBOARD_A] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_S))
        {
            game_input.keyboard_keys[KEYBOARD_S] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_D))
        {
            game_input.keyboard_keys[KEYBOARD_D] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_SPACE))
        {
            game_input.keyboard_keys[KEYBOARD_SPACE] = BUTTON_UP;
        }
        if (console_is_key_pressed((u32)VK_ESCAPE))
        {
            break;
        }
        
        if (!console_is_key_pressed((u32)VK_W))
        {
            game_input.keyboard_keys[KEYBOARD_W] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_A))
        {
            game_input.keyboard_keys[KEYBOARD_A] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_S))
        {
            game_input.keyboard_keys[KEYBOARD_S] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_D))
        {
            game_input.keyboard_keys[KEYBOARD_D] = BUTTON_DOWN;
        }
        if (!console_is_key_pressed((u32)VK_SPACE))
        {
            game_input.keyboard_keys[KEYBOARD_SPACE] = BUTTON_DOWN;
        }
        
        game_render_update(&game_input, snake, game_map, renderer);
        
#endif /* !defined(GUI_ENABLED)*/
        Sleep(150);
    }
    //system("PAUSE");
    
#if defined(GUI_ENABLED)
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);               
    while (!WindowShouldClose())    
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
        CloseWindow();       
    }
#endif // defined(GUI_ENABLED)
#if defined(DEBUG_MODE)
    if (snake == NULL)
        puts("Snake is probably freed, at least it has been NULLed");
    system("PAUSE");
#endif // defined(DEBUG_MODE)
    map_free(game_map);
    snake_free(&snake);
    console_renderer_destroy(renderer);
    return EXIT_SUCCESS;
}
