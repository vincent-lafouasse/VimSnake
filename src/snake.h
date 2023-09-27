#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "geometry.h"
#include "render.h"

#include <deque>

struct Snake
{
    Snake(TilePosition start, Sprite* head, Sprite* body);

    void advance(void);
    void set_direction(Direction direction);
    void render(Screen* screen);

    Direction m_direction;
    std::deque<TilePosition> m_body;
    Sprite* m_head_sprite;
    Sprite* m_body_sprite;
    int m_move_count;
};

#endif
