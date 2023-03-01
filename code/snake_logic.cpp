#include <stdlib.h>

#include "snake_logic.hpp"
#include "snake_map.hpp"


Snake::Snake(std::size_t start_x, std::size_t start_y)
{
    head_ = new SnakeChunk;
    head_->direction = ChunkDirection::None;
    head_->coord.x = start_x;
    head_->coord.y = start_y;
    head_->next = nullptr;
    head_->type = ChunkType::Head;
    state_ = SnakeState::Alive;
    speed_ = 1;
    tail_ = nullptr;
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    head_->prev = nullptr;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
}


void Snake::snake_chunk_add_speed(SnakeChunk* chunk, std::size_t speed)
{
    switch (chunk->direction) 
    {
        case ChunkDirection::Down: 
        {
            chunk->coord.y += speed;
            break;
        }
        case ChunkDirection::Up:
        {
            chunk->coord.y -= speed;
            break;
        }
        case ChunkDirection::Left:
        {
            chunk->coord.x -= speed;
            break;
        }
        case ChunkDirection::Right:
        {
            chunk->coord.x += speed;
            break;
        }
        case ChunkDirection::None: { break; }
    }
}


CollisionType Snake::snake_collision_check(Map* map)
{
    CollisionType result{};
    for (std::size_t map_y = 0; map_y < map->height(); map_y++)
    {
        for (std::size_t map_x = 0; map_x < map->width(); map_x++)
        {
            MapChunk* test_chunk = map->get_map_chunk(head_->coord.x, head_->coord.y);
            switch (test_chunk->type)
            {
                case ChunkType::Border:
                {
                    result = CollisionType::BORDER_COLLISION;
                    goto is_collided;
                }
                case ChunkType::Food:
                {
                    result = CollisionType::FOOD_COLLISION;
                    goto is_collided;
                }
                case ChunkType::Body: { break; }
                case ChunkType::Head: { break; }
                case ChunkType::Space: { break; }
                case ChunkType::Tail: { break; }
            }
        }
    }
    is_collided:

    SnakeChunk* temp_head = head_;
    
    while (head_->next != nullptr)
    {
        if (temp_head->coord.x == head_->next->coord.x &&
            temp_head->coord.y == head_->next->coord.y)
        {
            result = CollisionType::BODY_COLLISION;
            break;
        }
        head_ = head_->next;
    }
    head_ = temp_head;
    
    return result;
}


void Snake::die(void)
{
    state_ = SnakeState::Dead;
}


void Snake::snake_move()
{
    SnakeChunk* reserved_head = head_;
    
    while (head_ != nullptr) 
    {
        snake_chunk_add_speed(head_, speed_);
        head_ = head_->next;
    }
    head_ = reserved_head;
}


void Snake::snake_rotate()
{
    // NOTE(Venci): Change direction at snake's corners
    // TODO(Venci): Think and simplify this code by using doubly-linked snake
#if defined(SNAKE_DOUBLY_LINKED_LIST)
    SnakeChunk* reserved_tail = tail_;
    
    while (tail_ != NULL)
    {
        if (tail_->prev != NULL &&
            tail_->direction != tail_->prev->direction)
        {
            tail_->direction = tail_->prev->direction;
        }
        tail_ = tail_->prev;
    }
    tail_ = reserved_tail;
#elif defined(SNAKE_SINGLY_LINKED_LIST)
    SnakeChunk* reserved_head = head_;
    
    u32 snake_length = 0;
    
    while (head_ != NULL)
    {
        snake_length++;
        head_ = head_->next;
    }
    head_ = reserved_head;
    
    SnakeChunk** snake_stack = (SnakeChunk**)malloc(sizeof(SnakeChunk*) * (size_t)snake_length);
    
    u32 counter = 0;
    while (head_ != NULL)
    {
        snake_stack[counter++] = head_;
        head_ = head_->next;
    }
    head_ = reserved_head;
    
    for (u32 i = snake_length - 1; i > 0; i--)
    {
        SnakeChunk* next_chunk = snake_stack[i];
        SnakeChunk* prev_chunk = snake_stack[i - 1];
        
        if (next_chunk->direction != prev_chunk->direction)
        {
            next_chunk->direction = prev_chunk->direction;
        }
    }
    free(snake_stack);
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
}


void Snake::snake_grow(std::size_t size)
{
    /*
    NOTE(Venci): 
            size could be used for (ну что-то совсем не бонусная) bonus food, you eat it and grow by more
            than 1 chunk. 
    TODO(Venci):
        ) Have to check if there's enough space on the map
            and can we generate food further
        ) Limit size on map size.
    */
    
    SnakeChunk* temp_head = head_;
    SnakeChunk* new_tail_chunk;
    
    for (std::size_t i = 0; i < size; i++)
    {
        new_tail_chunk = (SnakeChunk*)malloc(sizeof(SnakeChunk));
        new_tail_chunk->next = nullptr;
        new_tail_chunk->type = ChunkType::Tail;
        
        
        if (tail_ == nullptr)
            new_tail_chunk->coord = head_->coord;
        else
            new_tail_chunk->coord = tail_->coord;
        
        new_tail_chunk->direction = head_->direction;
        
        switch (head_->direction)
        {
            case ChunkDirection::Down:
            {
                new_tail_chunk->coord.y--;
                break;
            }
            case ChunkDirection::Up:
            {
                new_tail_chunk->coord.y++;
                break;
            }
            case ChunkDirection::Left:
            {
                new_tail_chunk->coord.x++;
                break;
            }
            case ChunkDirection::Right:
            {
                new_tail_chunk->coord.x--;
                break;
            }
            case ChunkDirection::None: { break; }
        }
        
        while (head_->next != nullptr)
            head_ = head_->next;
        
#if defined(SNAKE_DOUBLY_LINKED_LIST)
        new_tail_chunk->prev = head_;
#endif // defined(SNAKE_DOUBLY_LINKED_LIST)
        
        head_->next = new_tail_chunk;
        tail_ = new_tail_chunk;
        
        if (head_->type != ChunkType::Head)
            head_->type = ChunkType::Body;
        head_ = temp_head;
    }
}


void Snake::set_head(SnakeChunk* new_head)
{
    head_ = new_head;
}


void Snake::head_next(void)
{
    head_ = head_->next;
}


SnakeChunk* Snake::head() const 
{
    return head_;
}

SnakeState Snake::state() const
{
    return state_;
}


Snake::~Snake()
{
    SnakeChunk* temp_head;
    
    while (head_ != NULL)
    {
        temp_head = head_->next;
        delete head_;
        head_ = temp_head;
    }
}


