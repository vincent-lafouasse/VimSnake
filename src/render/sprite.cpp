#include "sprite.h"

#include <iostream>

Sprite::Sprite()
{
    m_texture = nullptr;
    m_dimension = PixelDimension(0, 0);
}

Sprite::Sprite(const char* png_path, Screen* screen)
{
    int width, height;

    m_texture = IMG_LoadTexture(screen->m_renderer, png_path);
    SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);

    m_dimension.w = width;
    m_dimension.h = height;
}

void Sprite::render(PixelPosition position, Screen* screen)
{
    SDL_Rect dst_rect = {position.x, position.y, m_dimension.w, m_dimension.h};
    SDL_RenderCopy(screen->m_renderer, m_texture, NULL, &dst_rect);
}

void Sprite::render(PixelPosition position, float angle, Screen* screen)
{
    SDL_Rect dst_rect = {position.x, position.y, m_dimension.w, m_dimension.h};
    SDL_RenderCopyEx(screen->m_renderer, m_texture, NULL, &dst_rect, angle,
                     NULL, SDL_FLIP_NONE);
}

Sprite::~Sprite(void)
{
    SDL_DestroyTexture(m_texture);

    std::cout << "freeing sprite" << std::endl;
}
