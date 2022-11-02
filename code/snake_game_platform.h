/* date = November 2nd 2022 2:39 pm */

#ifndef SNAKE_GAME_PLATFORM_H
#define SNAKE_GAME_PLATFORM_H

/* keyboard virtual keys for GetAsyncKeyState */
#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

/* R.enderer C.onsole W.in */
#define RCW_API /*__declspec(dllexport)*/
/* R.enderer R.ayL.ib  */
#define RRL_API /*__declspec(dllexport)*/


#if defined(GUI_ENABLED)
# include "snake_renderer_raylib.h"
# define CURRENT_RENDERER RaylibRenderer
#else 
# include "snake_renderer_console_win.h"
# define CURRENT_RENDERER WinConsoleRenderer
#endif /* defined(GUI_ENABLED) */


typedef enum InputKeyboardKeys
{
    KEYBOARD_W,
    KEYBOARD_A,
    KEYBOARD_S,
    KEYBOARD_D,
    
    KEYBOARD_KEYS_COUNT
} InputKeyboardKeys;


typedef enum GameKeyState
{
    BUTTON_DOWN,
    BUTTON_UP,
    
    BUTTOn_STATES_COUNT
} GameKeyState;


typedef struct GameInput
{
    GameKeyState KeyboardKeys[KEYBOARD_KEYS_COUNT];
} GameInput;


#endif //SNAKE_GAME_PLATFORM_H
