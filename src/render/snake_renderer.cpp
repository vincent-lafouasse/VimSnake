#include "snake_renderer.h"

#include <iostream>

#define HEAD_PNG "./assets/trex_pixel/snake_head_right.png"
#define BODY_PNG "./assets/trex_pixel/snake_body.png"

void SnakeRenderer::render(Snake* snake, Screen* screen)
{
    auto it = snake->m_body.begin();

    assert(snake->m_body.size() > 0);

    head->render(it->to_pixelwise(screen->m_tile_size), screen);
    it++;

    while (it != snake->m_body.end())
    {
        body->render(it->to_pixelwise(screen->m_tile_size), screen);
        it++;
    }
}

SnakeRenderer::SnakeRenderer(Screen* screen)
{
    head = new Sprite(HEAD_PNG, screen);
    head->m_dimension = screen->m_tile_size;

    body = new Sprite(BODY_PNG, screen);
    body->m_dimension = screen->m_tile_size;
}

SnakeRenderer::~SnakeRenderer()
{
    delete head;
    delete body;
}
