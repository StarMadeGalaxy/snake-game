/* date = October 20th 2022 2:31 am */

#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <stdlib.h>
#include "snake_types.h"


static u16 get_random_number(u16 low, u16 high);
static void snake_move(SnakeChunk* head_chunk, ChunkDirection new_direction);
static void snake_eat(SnakeChunk* head_chunk, MapChunk* food_chunk);
static void snake_grow(SnakeChunk* head_chunk);
static void snake_free(SnakeChunk* head_chunk);


#endif //SNAKE_LOGIC_H
