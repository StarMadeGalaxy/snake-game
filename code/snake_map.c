#include "snake_map.h"


static MapChunk* get_map_chunk(Map* map, u16 x, u16 y)
{
    return &map->ptr[y * map->width + x];
}


static Map* map_alloc(u16 height, u16 width)
{
    Map* game_map = (Map*)malloc(sizeof(Map));
    game_map->ptr = (MapChunk*)malloc((size_t)height * (size_t)width  * sizeof(MapChunk*));
    game_map->height = height;
    game_map->width = width;
    return game_map;
}


static void map_init(Map* map)
{
    MapChunk* chunk;
    for (u16 x = 0; x < map->width; x++)
    {
        chunk = get_map_chunk(map, x, 0);
        chunk->type = Border;
        chunk->y = 0;
        chunk->x = x;
    }
    
    for (u16 y = 1; y < map->height - 1; y++)
    {
        chunk = get_map_chunk(map, 0, y);
        chunk->type = Border;
        chunk->x = 0;
        chunk->y = y;
        
        for (u16 x = 1; x < map->width - 1; x++)
        {
            chunk = get_map_chunk(map, x, y);
            chunk->type = Space;
            chunk->x = x;
            chunk->y = y;
        }
        u16 last_row_x = map->width - 1;
        chunk = get_map_chunk(map, last_row_x, y);
        chunk->type = Border;
        chunk->x = last_row_x;
        chunk->y = y;
    }
    
    for (u16 x = 0; x < map->width; x++)
    {
        u16 last_col_y = map->height - 1;
        chunk = get_map_chunk(map, x, last_col_y);
        chunk->type = Border;
        chunk->x = x;
        chunk->y = last_col_y;
    }
}


static void map_free(Map* map)
{
    free(map->ptr);
}