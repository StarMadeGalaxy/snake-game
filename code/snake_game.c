#include "snake_game.h"
#include <Windows.h>
#include <time.h>


#pragma warning( disable : 4554 )

int main(int arg_count, char* arg_array[])
{
    srand((u32)time(NULL)); 
    
    const u16 screen_width = 10;
    const u16 screen_height = 15;
    /*
NOTE(Venci):
 Should i pass screen_buffer through the game_map->ptr
to the renderer? Or maybe do it directly?
    */
    Map* game_map = map_alloc(screen_height, screen_width);
    map_init(game_map);
    
    Snake* snake = snake_alloc();
    snake_init(snake, (u16)(screen_width / 2), (u16)(screen_height / 2), None);
    
#if !defined(GUI_ENABLED)
    WinConsoleRenderer* renderer = console_renderer_create(screen_height, screen_width);
#endif // !defined(GUI_ENABLED)
    
    GameInput game_input;
    
    // NOTE(Venci): this entire file should GUI_ENABLED independent 
    for (;;)
    {
#if !defined(GUI_ENABLED)
        
        console_cursor_begin_move(renderer);;
        
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
        if (console_is_key_pressed((u32)VK_ESCAPE))
        {
            fputs("[Bye!]\n", stdout);
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
        
        game_render_update(&game_input, snake, game_map, renderer);
        
#endif /* !defined(GUI_ENABLED)*/
        Sleep(100);
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
    map_free(game_map);
    snake_free(snake);
    
    return 0;
}
