#include "snake.h"

#include <cassert>

#define START_LEN 3

void Snake::advance(void)
{
    TilePosition delta = TilePosition(0, 0);

    switch (m_direction)
    {
        case Direction::Up:
        {
            delta.y = -1;
            break;
        }
        case Direction::Down:
        {
            delta.y = 1;
            break;
        }
        case Direction::Left:
        {
            delta.x = -1;
            break;
        }
        case Direction::Right:
        {
            delta.x = 1;
            break;
        }
    }

    m_body.push_front(m_body.front() + delta);

    m_move_count++;

    if (m_move_count >= START_LEN)
    {
        m_body.pop_back();
    }
}

Snake::Snake(TilePosition start)
{
    m_body.push_front(start);
    m_direction = Direction::Down;
    m_move_count = 0;
}

void Snake::set_direction(Direction direction)
{
    if (direction == opposite_direction(m_direction))
        return;
    m_direction = direction;
}
