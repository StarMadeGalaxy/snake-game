/* date = October 20th 2022 8:31 pm */

#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "snake_types.h"


static MapChunk* get_map_chunk(Map* map, u16 x, u16 y);
static Map* map_alloc(u16 height, u16 width);
static void map_init(Map* map);
static void map_free(Map* map);


#endif //SNAKE_MAP_H
