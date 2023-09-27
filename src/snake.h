#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "geometry.h"
#include "render.h"

#include <deque>

struct Snake
{
    Snake(TilePosition start);

    void advance(void);
    void set_direction(Direction direction);

    Direction m_direction;
    std::deque<TilePosition> m_body;
    int m_move_count;
};

#endif
