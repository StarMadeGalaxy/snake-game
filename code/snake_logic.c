#include "snake_logic.h"


internal u16 get_random_number(u16 low, u16 high)
{
    return (((u16)rand() % (high - low + 1)) + low); 
}


internal void snake_chunk_add_speed(SnakeChunk* chunk, u16 speed)
{
    switch (chunk->direction) 
    {
        case Down: 
        {
            chunk->y += speed;
            break;
        }
        case Up:
        {
            chunk->y -= speed;
            break;
        }
        case Left:
        {
            chunk->x -= speed;
            break;
        }
        case Right:
        {
            chunk->x += speed;
            break;
        }
    }
}


internal CollisionType snake_collision_check(Snake* snake, Map* map)
{
    // NOTE(Venci): maybe implement a special enum with collision type?
    CollisionType result;
    for (u16 map_y = 0; map_y < map->height; map_y++)
    {
        for (u16 map_x = 0; map_x < map->width; map_x++)
        {
            MapChunk* test_chunk = get_map_chunk(map, snake->head->x, snake->head->y);
            switch (test_chunk->type)
            {
                case Border:
                {
                    // NOTE(Venci): I really hope that this is legal goto usage
                    // i saw usage like that in linux kernel style guide!
                    result = BORDER_COLLISION;
                    goto collision_return;
                }
            }
        }
    }
    
    SnakeChunk* temp_head = snake->head;
    
    while (snake->head)
    {
        
        snake->head = snake->head->next;
    }
    snake->head = temp_head;
    
    collision_return:
    return result;
}


internal void snake_move(Snake* snake)
{
    SnakeChunk* reserved_head = snake->head;
    
    while (snake->head != NULL) 
    {
        snake_chunk_add_speed(snake->head, snake->speed);
        snake->head = snake->head->next;
    }
    snake->head = reserved_head;
    
#if defined(SNAKE_ROTATION_ON)
    // When snake moves, chunks at the nodes change 
    // TODO(Venci): To avoid access violation we have to check next for NULL
    while (snake->head->next != NULL)
    {
        ChunkDirection head_dir = snake->head->direction;
        ChunkDirection next_dir = snake->head->next->direction;
        
        if (head_dir != next_dir)
        {
            snake->head->direction = next_dir;
        }
        snake->head = snake->head->next;
    }
    snake->head = reserved_head;
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
size could be used for (ну что-то совсем не бонусная) bonus food, you eat it and grow by more
than 1 chunk. 
TODO(Venci):
Have to check if there's enough space on the map
and can we generate food further
*/
    
    SnakeChunk* new_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    
    if (snake->tail == NULL)
    {
        snake->tail = new_chunk;
    }
}



internal void snake_init(Snake* snake, 
                         u16 start_x, 
                         u16 start_y, 
                         ChunkDirection start_direction)
{
    snake->head->direction = start_direction;
    snake->head->x = start_x;
    snake->head->y = start_y;
    snake->head->next = NULL;
    snake->head->type = Head;
    snake->state = Alive;
    snake->speed = 1;
    snake->tail = NULL;
}


internal Snake* snake_alloc()
{
    Snake* new_snake = (Snake*)malloc(sizeof(Snake));
    new_snake->head = (SnakeChunk*)malloc(sizeof(SnakeChunk));
    return new_snake;
}


internal void snake_free(Snake** snake)
{
    SnakeChunk* temp_head;
    Snake* snake_pointer = *snake;
    
    while (snake_pointer->head != NULL)
    {
        temp_head = snake_pointer->head->next;
        free(snake_pointer->head);
        snake_pointer->head = temp_head;
    }
    free(snake_pointer);
    *snake = NULL;
}


#if defined(DEBUG_MODE)
#endif


