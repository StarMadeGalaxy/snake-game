/* date = October 20th 2022 2:31 am */

#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include "snake_types.h"


internal u16 get_random_number(u16 low, u16 high);
internal void snake_move(Snake* snake, ChunkDirection new_direction);
internal void snake_eat(Snake* snake, MapChunk* food_chunk);
internal void snake_grow(Snake* snake);
internal void snake_free(Snake* snake);


#endif //SNAKE_LOGIC_H
