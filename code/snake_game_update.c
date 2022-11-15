/* date = November 2nd 2022 2:31 pm */


#include "snake_game_platform.h"
#include "base_types.h"
#include "snake_logic.h"


internal void game_render_update(GameInput* input,
                                 Snake* snake,
                                 Map* game_map,
                                 CURRENT_RENDERER* renderer)
{
#if defined(DEBUG_MODE)
    if (input->keyboard_keys[KEYBOARD_SPACE])
    {
        snake->head->direction = None;
    }
#endif // defined(DEBUG)
    if (input->keyboard_keys[KEYBOARD_W])
    {
        snake->head->direction = Up;
    }
    if (input->keyboard_keys[KEYBOARD_A])
    {
        snake->head->direction = Left;
    }
    if (input->keyboard_keys[KEYBOARD_S])
    {
        snake->head->direction = Down;
    }
    if (input->keyboard_keys[KEYBOARD_D])
    {
        snake->head->direction = Right;
    }
    
    if (snake->head->direction != None)
    {
        snake_move(snake);
    }
    
    CollisionType snake_collision = snake_collision_check(snake, game_map);
    
    switch (snake_collision)
    {
        case BORDER_COLLISION:
        {
            snake->state = Dead;
        }
        case BODY_COLLISION:
        {
            snake->state = Dead;
        }
    }
    
    console_cursor_begin_move(renderer);
    console_make_frame(renderer, snake, game_map);
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
    
    // SPACE
    if (input->keyboard_keys[KEYBOARD_SPACE] == BUTTON_UP)
        fprintf(stdout, "Space key is pressed %d                 \n", test_var);
    else if (input->keyboard_keys[KEYBOARD_SPACE] == BUTTON_DOWN)
        fprintf(stdout, "Space key is unpressed %d               \n", test_var);
    
    fprintf(stdout, "snake->head->dn  : %d\n", snake->head->direction);
    fprintf(stdout, "Snake->head->x   : %d\n", snake->head->x);
    fprintf(stdout, "snake->head->type: %d\n", snake->head->type);
    fprintf(stdout, "snake->head->y   : %d\n", snake->head->y);
    fprintf(stdout, "snake->tail      : %p\n", snake->tail);
    fprintf(stdout, "snake->head->next: %p\n", snake->head->next);
    fprintf(stdout, "snake->head      : %p\n", snake->head);
    
    test_var++;
#endif // defined(DEBUG_MODE) 
}