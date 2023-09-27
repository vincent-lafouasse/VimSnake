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

    TilePosition old_head = m_body.front();
    TilePosition new_head =
        TilePosition(old_head.x + delta.x, old_head.y + delta.y);
    m_body.push_front(new_head);
    if (m_move_count >= START_LEN - 1)
        m_body.pop_back();
    m_move_count++;
}

Snake::Snake(TilePosition start, Sprite* head, Sprite* body)
{
    m_body.push_front(start);
    m_head_sprite = head;
    m_body_sprite = body;
    m_direction = Direction::Down;
    m_move_count = 0;
}

void Snake::set_direction(Direction direction)
{
    if (direction == opposite_direction(m_direction))
        return;
    m_direction = direction;
}

void Snake::render(Screen* screen)
{
    auto it = m_body.begin();

    assert(m_body.size() > 0);

    m_head_sprite->render(it->to_pixelwise(screen->m_tile_size), screen);
    it++;

    while (it != m_body.end())
    {
        m_body_sprite->render(it->to_pixelwise(screen->m_tile_size), screen);
        it++;
    }
}
