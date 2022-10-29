#include "snake_game.h"


int main(int ArgCount, char* ArgS[])
{
    srand(time(NULL)); 
    
    const u16 screenWidth = 10;
    const u16 screenHeight = 15;
    
    Map* game_map = map_alloc(screenHeight, screenWidth);
    map_init(game_map);
    console_render_frame(game_map);
    
    
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


