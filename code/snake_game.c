#include "snake_game.h"
#include <Windows.h>


#pragma warning( disable : 4554 )

int main(int arg_count, char* arg_array[])
{
    /*srand(time(NULL)); */
    
    const u16 screen_width = 10;
    const u16 screen_height = 15;
    
    Map* game_map = map_alloc(screen_height, screen_width);
    map_init(game_map);
    
    WinConsoleRenderer* renderer = console_renderer_alloc();
    console_renderer_init(renderer, screen_height, screen_width);
    
    GameInput game_input;
    
    
    for (;;)
    {
#if !defined(GUI_ENABLED)
        
        static int test_var = 0;
        if (test_var >= 100)
        {
            test_var = 0;
        }
        
        console_cursor_begin_move(renderer);
        console_render_frame(renderer);
        
        if (console_is_key_pressed((u32)VK_W))
        {
            game_input.keyboard_keys[KEYBOARD_W] = BUTTON_UP;
            fprintf(stdout, "W key pressed %d\n", test_var);
        }
        else if (console_is_key_pressed((u32)VK_A))
        {
            game_input.keyboard_keys[KEYBOARD_A] = BUTTON_UP;
            fprintf(stdout, "A key pressed %d\n", test_var);
        }
        else if (console_is_key_pressed((u32)VK_S))
        {
            game_input.keyboard_keys[KEYBOARD_S] = BUTTON_UP;
            fprintf(stdout, "S key pressed %d\n", test_var);
        }
        else if (console_is_key_pressed((u32)VK_D))
        {
            game_input.keyboard_keys[KEYBOARD_D] = BUTTON_UP;
            fprintf(stdout, "D key pressed %d\n", test_var);
        }
        else if (console_is_key_pressed((u32)VK_ESCAPE))
        {
            fputs("Bye!                         \n", stdout);
            break;
        }
        
        test_var++;
#endif /* !defined(GUI_ENABLED)*/
    }
    system("PAUSE");
    
    /*
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);               
    
    while (!WindowShouldClose())    
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        
        EndDrawing();
    
    
    CloseWindow();       
    */
    map_free(game_map);
    return 0;
}
