/* date = October 28th 2022 0:36 am */

#if !defined(SNAKE_GAME_H)
#define SNAKE_GAME_H

#include "snake_game_platform.hpp"

#include "snake_map.cpp"
#include "snake_logic.cpp"

#if !defined(GUI_ENABLED) && defined(_WIN32)
#   include "snake_game_console_win32.cpp"
#endif // !defined(GUI_ENABLED) && defined(_WIN32)

#if !defined(GUI_ENABLED) && defined(__linux__)
#   include "snake_renderer"
#endif // !defined(GUI_ENABLED) && defined(__linux__)

#if defined(GUI_ENABLED)
#   include "snake_game_sdl.cpp"
#endif // defined(GUI_ENABLED)

#endif //SNAKE_GAME_H
