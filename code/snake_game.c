#include "snake_game.h"
#include <Windows.h>


#pragma warning( disable : 4554 )

int main(int ArgCount, char* ArgS[])
{
    /*srand(time(NULL)); */
    
    const u16 screenWidth = 10;
    const u16 screenHeight = 15;
    
    Map* game_map = map_alloc(screenHeight, screenWidth);
    map_init(game_map);
    
    WinConsoleRenderer* renderer = console_renderer_alloc();
    console_renderer_init(renderer);
    
    for (;;)
    {
        console_cursor_begin_move(renderer);
        console_render_frame(game_map);
        
        if ((GetAsyncKeyState((u32)VK_W) & MSB(u16)) != 0)
        {
            fputs("W key pressed", stdout);
        }
        else if ((GetAsyncKeyState((u32)VK_A) & MSB(u16)) != 0)
        {
            fputs("A keyy pressed", stdout);
        }
        else if ((GetAsyncKeyState((u32)VK_S) & MSB(u16)) != 0)
        {
            fputs("S key pressed", stdout);
        }
        else if ((GetAsyncKeyState((u32)VK_D) & MSB(u16)) != 0)
        {
            fputs("D key pressed", stdout);
        }
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
    }
    
    CloseWindow();       
    */
    map_free(game_map);
    return 0;
}