#if !defined(SNAKE_H)
#define SNAKE_H

#include <memory>

#include <Windows.h>

struct Position
{
    int x;
    int y;
};

enum class SnakeDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

void Run(HANDLE& console, std::unique_ptr<char[]>& screen_buffer, unsigned long& bytes_written);

void update_food_pos(std::unique_ptr<char[]>& screen_buffer, Position& food);

#endif // SNAKE_H