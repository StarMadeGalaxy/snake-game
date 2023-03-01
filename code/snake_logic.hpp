/* date = October 20th 2022 2:31 am */

#if !defined(SNAKE_LOGIC_H)
#define SNAKE_LOGIC_H

#include "snake_types.hpp"
#include "snake_map.hpp"


class Snake
{
public:  
    Snake(std::size_t start_x, std::size_t start_y);
    CollisionType snake_collision_check(Map* map);
    void snake_grow(std::size_t size);
    void snake_rotate(void);
    void snake_move(void);
    void head_next(void);
    void die(void);
    void set_head(SnakeChunk* new_head);
    SnakeChunk* head() const;
    SnakeState state() const;
    ~Snake();
private:
    Snake* snake_alloc(void);
    void snake_chunk_add_speed(SnakeChunk* chunk, std::size_t);
    void snake_init(Snake* snake, std::size_t start_x, 
                    std::size_t start_y, ChunkDirection start_direction);
private:
    SnakeChunk* head_;
    SnakeChunk* tail_;
    enum class SnakeState state_;
    std::size_t speed_;
};


#endif //SNAKE_LOGIC_H
