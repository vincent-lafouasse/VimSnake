#pragma once

#include "screen.h"
#include "snake.h"
#include "sprite.h"

struct SnakeRenderer
{
    SnakeRenderer(Screen* screen);
    ~SnakeRenderer();

    void render(Snake* snake, Screen* screen);

    Sprite* head;
    Sprite* body;
};
