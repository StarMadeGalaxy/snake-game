#include <cstdlib>
#include <iostream>

#include "snake_game_platform.hpp"
#include "../vendor/SDL2/include/SDL.h"


namespace {
    std::size_t screen_height = 720;
    std::size_t screen_width = 1280;
}


struct GameRenderer
{
    SDL_Window* window;
    SDL_Surface* surface;
};


void IPlatformAPI::renderer_create(void)
{
    renderer = std::make_unique<GameRenderer>();
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed. Error: " << SDL_GetError() << ENDL;
        std::exit(EXIT_FAILURE);
    } 
    else 
    {
        renderer->window = SDL_CreateWindow(
            "Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            static_cast<int>(screen_width), static_cast<int>(screen_height), 
            SDL_WINDOW_SHOWN);

        if (renderer->window == NULL)
        {
            std::cerr << "SDL_CreateWindow failed. Error: " << SDL_GetError() << ENDL;
            std::exit(EXIT_FAILURE);
        }
    }
}


IPlatformAPI::IPlatformAPI() :
        screen_height_(screen_height), screen_width_(screen_width) 
{
    platform_active = true;
    renderer_create();
}


void IPlatformAPI::render_frame(Snake *snake, Map *map)
{
    (void)snake;
    (void)map;
    auto window_stay_up = []()
    { 
        SDL_Event e; bool quit = false; 
        while( quit == false ) 
        { while(SDL_PollEvent(&e)) { if( e.type == SDL_QUIT ) { quit = true; } } }
    };

     
    renderer->surface = SDL_GetWindowSurface(renderer->window);
    SDL_FillRect(renderer->surface, 
        NULL, SDL_MapRGB(renderer->surface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(renderer->window);
    //window_stay_up();
}


IPlatformAPI::~IPlatformAPI()
{
    SDL_DestroyWindow(renderer->window);
    SDL_Quit();
}