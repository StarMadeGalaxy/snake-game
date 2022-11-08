#include "snake_logic.h"


internal u16 get_random_number(u16 low, u16 high)
{
    return (((u16)rand() % (high - low + 1)) + low); 
}


internal void snake_move(Snake* snake, ChunkDirection new_direction)
{
#if 0
    for (snake->head->hext != NULL)
    {
        switch (chunk.) {
            case ch_dir::Down:
            {
                size_t current_y = chunk.get_y();
                chunk.set_y(current_y + 1);
                break;
            }
            case ch_dir::Up:
            {
                size_t current_y = chunk.get_y();
                chunk.set_y(current_y - 1);
                break;
            }
            case ch_dir::Left:
            {
                size_t current_x = chunk.get_x();
                chunk.set_x(current_x - 1);
                break;
            }
            case ch_dir::Right:
            {
                size_t current_x = chunk.get_x();
                chunk.set_x(current_x + 1);
                break;
            }
            default:
            break;
        }
    }
    // When snake moves, chunks at the nodes change 
    for (size_t i = snake_body.size() - 1; i > 0; i--)
    {
        ch_dir prev_node_dir = snake_body[i].get_direction();
        ch_dir next_node_dir = snake_body[i - 1].get_direction();
        if (next_node_dir != prev_node_dir)
        {
            snake_body[i].set_direction(next_node_dir);
        }
        ;
    }
#endif
}


internal void snake_eat(Snake* snake, MapChunk* food_chunk)
{
    ;
}


internal void snake_grow(Snake* snake, u32 size)
{
    /*
NOTE(Venci): 
size could be used for bonus food, you eat it and grows by more
than 1 chunk. 
TODO(Venci):
Have to check if there's enough space on the map
and can we generate food further
*/
    
    SnakeChunk* new_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    
    
}


internal void snake_free(Snake* snake)
{
    SnakeChunk head = snake->head;
    while (snake->head->next != NULL)
    {
        free(snake->head->next);
        snake->head->next = snake->head->next->next;
    }
    free(snake->head);
    free(snake);
}


#if defined(DEBUG)

#endif



#if 0
#endif 