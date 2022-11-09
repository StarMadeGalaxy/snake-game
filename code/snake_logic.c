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
            case Down:
            {
                size_t current_y = chunk.get_y();
                chunk.set_y(current_y + 1);
                break;
            }
            case Up:
            {
                size_t current_y = chunk.get_y();
                chunk.set_y(current_y - 1);
                break;
            }
            case Left:
            {
                size_t current_x = chunk.get_x();
                chunk.set_x(current_x - 1);
                break;
            }
            case Right:
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
size could be used for bonus food, you eat it and grow by more
than 1 chunk. 
TODO(Venci):
Have to check if there's enough space on the map
and can we generate food further
*/
    
    SnakeChunk* new_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    while(snake->head);
    
}


internal void snake_init(Snake* snake, 
                         u16 start_x, 
                         u16 start_y, 
                         ChunkDirection start_direction)
{
    snake->head->direction = start_direction;
    snake->tail->direction = start_direction;
    
    snake->head->x = start_x;
    snake->tail->x = start_x;
    
    snake->head->y = start_y;
    snake->tail->y = start_y;
    
    snake->head->type = Head;
    snake->tail->type = Tail;
    
    snake->head->next = NULL;
    snake->tail->next = NULL;
    
    snake->state = Alive;
}


internal Snake* snake_alloc()
{
    Snake* new_snake = (Snake*)malloc(sizeof(Snake));
    new_snake->head = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    new_snake->tail = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    return new_snake;
}


internal void snake_free(Snake* snake)
{
    SnakeChunk* head = snake->head;
    while (head->next != NULL)
    {
        free(head->next);
        head->next = head->next->next;
    }
    free(head);
    free(snake);
}


#if defined(DEBUG)

#endif



#if 0
#endif 