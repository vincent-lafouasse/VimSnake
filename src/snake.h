#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "geometry.h"
#include "render.h"

#include <deque>

class Snake
{
   public:
    Snake(TilePosition start, Sprite* sprite);

    void render(Screen* screen, PixelDimension tile_size);

   private:
    std::deque<TilePosition> m_body;
    Sprite* m_sprite;
};

#endif
