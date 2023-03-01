#if !defined(SNAKE_MAP_H)
#define SNAKE_MAP_H

#include "snake_types.hpp"


template<typename T> 
T get_random_number(T lower, T upper);


class Map
{
public:
    Map(std::size_t height_, std::size_t width_);
    MapChunk* get_map_chunk(std::size_t x, std::size_t y);
    std::size_t height() const;
    std::size_t width() const;
    MapChunk* food_chunk() const;
    Coordinates food_generate(void);
    ~Map();
private:
    void map_init(void);
private:
    std::size_t height_;
    std::size_t width_;
    MapChunk* ptr;
    // NOTE(Venci): temp solution
    MapChunk* food_chunk_;
};


#endif //SNAKE_MAP_H
