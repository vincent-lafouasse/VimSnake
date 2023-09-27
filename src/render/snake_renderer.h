#pragma once

#include "screen.h"
#include "snake.h"
#include "sprite.h"

struct SnakeRenderer
{
    SnakeRenderer();
    SnakeRenderer(Screen* screen);
    void render(Snake* snake, Screen* screen);

    Sprite head;
    Sprite body;
};
