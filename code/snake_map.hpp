#if !defined(SNAKE_MAP_H)
#define SNAKE_MAP_H

#include "snake_types.hpp"


function u16 get_random_number(u16 lower, u16 upper);
function Coordinates food_generate(Map* map);
function MapChunk* get_map_chunk(Map* map, u16 x, u16 y);
function Map* map_alloc(u16 height, u16 width);
function void map_init(Map* map);
function void map_free(Map* map);

#if defined(DEBUG_MODE)
internal void spawn_food_coord(Map* map, u16 x, u16 y);
#endif // defined(DEBUG_MODE)


#endif //SNAKE_MAP_H
