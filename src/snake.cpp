#include "snake.h"

#include <cassert>

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
    // m_body.pop_back();
}

Snake::Snake(TilePosition start, Sprite* head, Sprite* body, Screen* screen)
{
    m_screen = screen;
    m_body.push_front(start);
    m_head_sprite = head;
    m_body_sprite = body;
    set_direction(Direction::Up);
}

void Snake::set_direction(Direction direction)
{
    m_direction = direction;
}

void Snake::render(PixelDimension tile_size)
{
    auto it = m_body.begin();

    assert(m_body.size() > 0);

    m_head_sprite->render(it->to_pixelwise(tile_size), m_screen);
    it++;

    while (it != m_body.end())
    {
        m_body_sprite->render(it->to_pixelwise(tile_size), m_screen);
        it++;
    }
}
