#include "snake.h"

Snake::Snake(TilePosition start, Sprite* sprite)
{
    m_body.push_front(start);
    m_sprite = sprite;
}

void Snake::render(Screen* screen, PixelDimension tile_size)
{
    auto it = m_body.begin();
    PixelPosition px_pos;

    while (it != m_body.end())
    {
        px_pos.x = it->x * tile_size.w;
        px_pos.y = it->y * tile_size.h;
        m_sprite->render(px_pos, screen);
        it++;
    }
}
