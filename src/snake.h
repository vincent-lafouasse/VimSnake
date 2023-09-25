#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "geometry.h"
#include "render.h"

#include <deque>

class Snake
{
   public:
    Snake(TilePosition start, Sprite* head, Sprite* body, Screen* screen);

    void advance(void);
    void set_direction(Direction direction);
    void render(PixelDimension tile_size);

   private:
    Direction m_direction;
    std::deque<TilePosition> m_body;
    Sprite* m_head_sprite;
    Sprite* m_body_sprite;
    Screen* m_screen;
};

#endif
