/* date = October 20th 2022 2:31 am */

#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "snake_types.h"


internal u16 get_random_number(u16 low, u16 high);
internal void snake_move(Snake* snake);
internal void snake_eat(Snake* snake, MapChunk* food_chunk);
internal void snake_grow(Snake* snake, u32 size);
internal void snake_free(Snake** snake);
internal Snake* snake_alloc();
internal void snake_add_speed(SnakeChunk* chunk, u16 speed);
internal void snake_init(Snake* snake, 
                         u16 start_x, 
                         u16 start_y,
                         ChunkDirection start_direction);
//internal void snake_chunk_init(SnakeChunk* chunk,
//u16 x, 
//u16 y,
//ChunkDirection direction);
//

#endif //SNAKE_LOGIC_H
