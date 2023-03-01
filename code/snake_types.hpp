/* date = October 20th 2022 2:05 am */

#if !defined(SNAKE_TYPES_H)
#define SNAKE_TYPES_H

#include <cstddef>

#include "snake_game_base_types.hpp"


enum class ChunkDirection
{
    None, Up, Left, Down, Right
};


enum class ChunkType
{
    Tail, Head, Body, Food, Border, Space
};


enum class SnakeState
{
    Alive, Dead
};


enum class CollisionType
{
    NONE_COLLISION, BORDER_COLLISION, BODY_COLLISION, FOOD_COLLISION
};


/* TODO(Venci): Implement key-value data structure to store chunk symbol there */
#if !defined(GUI_ENABLED)
#   define HEAD_CHAR '@'
#   define BODY_CHAR 'o'
#   define TAIL_CHAR '*'
#   define BORDER_CHAR '#'
#   define FOOD_CHAR '$'
#   define SPACE_CHAR ' '
#endif // defined(GUI_ENABLED)


struct Coordinates
{
    std::size_t x;
    std::size_t y;
};


struct SnakeChunk
{
    enum class ChunkDirection direction;
    enum class ChunkType type;
    struct SnakeChunk* next;
    Coordinates coord;
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    struct SnakeChunk* prev;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
};


struct MapChunk
{
    enum class ChunkType type;
    Coordinates coord;
};


#endif /* SNAKE_TYPES_H */
