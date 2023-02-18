#include "snake_types.hpp"

#include <windows.h>

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44


typedef char CONSOLE_FRAME_TYPE;


struct ConsoleSize
{
    u16 height;
    u16 width;
};


struct GameRenderer
{
    ConsoleSize size; 
    void* frame_data;

    HANDLE console_handler;
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
};