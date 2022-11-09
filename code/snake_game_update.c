/* date = November 2nd 2022 2:31 pm */


#include "snake_game_platform.h"
#include "base_types.h"


internal void game_render_update(GameInput* input,
                                 Snake* snake,
                                 Map* game_map,
                                 CURRENT_RENDERER* renderer)
{
    if (input->keyboard_keys[KEYBOARD_W])
    {
        
    }
    if (input->keyboard_keys[KEYBOARD_A])
    {
        
    }
    if (input->keyboard_keys[KEYBOARD_S])
    {
        
    }
    if (input->keyboard_keys[KEYBOARD_D])
    {
        
    }
    
    console_render_frame(renderer);
#if defined(DEBUG_MODE)
    local int test_var;
    
    if (test_var >= 100) test_var = 0;
    
    // W
    if (input->keyboard_keys[KEYBOARD_W] == BUTTON_UP)
        fprintf(stdout, "W key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_W] == BUTTON_DOWN)
        fprintf(stdout, "W key is unpressed %d               \n", test_var);
    
    // A
    if (input->keyboard_keys[KEYBOARD_A] == BUTTON_UP)
        fprintf(stdout, "A key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_A] == BUTTON_DOWN)
        fprintf(stdout, "A key is unpressed %d               \n", test_var);
    
    // S
    if (input->keyboard_keys[KEYBOARD_S] == BUTTON_UP)
        fprintf(stdout, "S key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_S] == BUTTON_DOWN)
        fprintf(stdout, "S key is unpressed %d               \n", test_var);
    
    // D
    if (input->keyboard_keys[KEYBOARD_D] == BUTTON_UP)
        fprintf(stdout, "D key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_D] == BUTTON_DOWN)
        fprintf(stdout, "D key is unpressed %d               \n", test_var);
    
    fprintf(stdout, "Last frame bytes written: %d               \n", renderer->bytes_written_last_frame);
    test_var++;
#endif // defined(DEBUG_MODE) 
}