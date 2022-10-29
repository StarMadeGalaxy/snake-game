#include "snake_logic.h"


static u16 get_random_number(u16 low, u16 high)
{
    return ((u16)rand() % (high - low + 1)) + low; 
}


static void snake_move(SnakeChunk* head_chunk, ChunkDirection new_direction)
{
    ;
}


void snake_eat(SnakeChunk* head_chunk, MapChunk* food_chunk)
{
    ;
}


void snake_grow(SnakeChunk* head_chunk)
{
    SnakeChunk* new_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
}


void snake_free(SnakeChunk* snake_head)
{
    ;
}