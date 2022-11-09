/* date = October 20th 2022 2:05 am */

#ifndef SNAKE_TYPES_H
#define SNAKE_TYPES_H

#include "base_types.h"


typedef enum ChunkDirection
{
    Up, Down, Left, Right, None
} ChunkDirection;


typedef enum ChunkType
{
    Tail, Head, Body, Food, Border, Space
} ChunkType;


typedef enum SnakeState
{
    Alive, Dead
} SnakeState;


/* TODO(Venci): Implement key-value data structure to store chunk symbol there */
#if !defined(GUI_ENABLED)
# define HEAD_CHAR '@'
# define BODY_CHAR '*'
# define FOOD_CHAR '$'
# define BORDER_CHAR '#'
# define SPACE_CHAR ' '
#endif // defined(GUI_ENABLED)




typedef struct SnakeChunk
{
    ChunkDirection direction;
    ChunkType type;
    struct SnakeChunk* next;
    /* struct SnakeChunk* prev; */
    u16 x;
    u16 y;
} SnakeChunk;


typedef struct MapChunk
{
    ChunkType type;
    u16 x;
    u16 y;
} MapChunk;


typedef struct Snake
{
    SnakeChunk* head;
    SnakeChunk* tail;
    SnakeState state;
} Snake;


typedef struct Map
{
    u16 height;
    u16 width;
    MapChunk* ptr;
} Map;


#endif /* SNAKE_TYPES_H */
