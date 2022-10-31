#include "snake_game.h"


int main(int ArgCount, char* ArgS[])
{
    srand(time(NULL)); 
    
    const u16 screenWidth = 10;
    const u16 screenHeight = 15;
    
    Map* game_map = map_alloc(screenHeight, screenWidth);
    map_init(game_map);
    
    WinConsoleRenderer* renderer = console_renderer_alloc();
    console_renderer_init(renderer);
    
    for (int i = 0; i < 1000; i++)
    {
        console_cursor_begin_move(renderer);
        console_render_frame(game_map);
        printf("%d\n", i);
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


