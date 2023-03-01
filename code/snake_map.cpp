#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "snake_map.hpp"


template<typename T>
T get_random_number(T lower, T upper)
{
    // std::random_device rd;
    // std::uniform_int_distribution<T> dist(lower, upper);
    return (rand() % (upper + 1 - lower) + lower);
}


Coordinates Map::food_generate()
{
    // NOTE(Venci): -2 due to border and first index is 0
    Coordinates food_coord;
    MapChunk* food_chunk_ptr;
    
    do {
        food_coord.x = get_random_number<std::size_t>(1, width_ - 2);
        food_coord.y = get_random_number<std::size_t>(1, height_ - 2);
        food_chunk_ptr = get_map_chunk(food_coord.x, food_coord.y);
    } while (food_chunk_ptr->type != ChunkType::Space);
    
    food_chunk_ptr->type = ChunkType::Food;
    food_chunk_ = food_chunk_ptr;
    return food_coord;
}


MapChunk* Map::food_chunk() const 
{
    return food_chunk_;
}


std::size_t Map::height() const
{
    return height_;
}


std::size_t Map::width() const
{
    return width_;
}


MapChunk* Map::get_map_chunk(std::size_t x, std::size_t y)
{
    return &ptr[y * width_ + x];
}


Map::Map(std::size_t height, std::size_t width) : 
    height_(height), width_(width)
{
    ptr = (MapChunk*)malloc(height * width * sizeof(MapChunk*));
    map_init();
}


void Map::map_init()
{
    MapChunk* chunk;
    for (std::size_t x = 0; x < width_; x++)
    {
        chunk = get_map_chunk(x, 0);
        chunk->type = ChunkType::Border;
        chunk->coord.y = 0;
        chunk->coord.x = x;
    }
    
    for (std::size_t y = 1; y < height_ - 1; y++)
    {
        chunk = get_map_chunk(0, y);
        chunk->type = ChunkType::Border;
        chunk->coord.x = 0;
        chunk->coord.y = y;
        
        for (std::size_t x = 1; x < width_ - 1; x++)
        {
            chunk = get_map_chunk(x, y);
            chunk->type = ChunkType::Space;
            chunk->coord.x = x;
            chunk->coord.y = y;
        }
        std::size_t last_row_x = width_ - 1;
        chunk = get_map_chunk(last_row_x, y);
        chunk->type = ChunkType::Border;
        chunk->coord.x = last_row_x;
        chunk->coord.y = y;
    }
    
    for (size_t x = 0; x < width_; x++)
    {
        std::size_t last_col_y = height_ - 1;
        chunk = get_map_chunk(x, last_col_y);
        chunk->type = ChunkType::Border;
        chunk->coord.x = x;
        chunk->coord.y = last_col_y;
    }
    // NOTE(Venci): temp solution
    food_chunk_ = ptr;
}


Map::~Map()
{
    free(ptr);
}


