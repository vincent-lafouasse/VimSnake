#include "sprite.h"

#include <iostream>

Sprite::Sprite()
{
    m_surface = nullptr;
    m_texture = nullptr;
    m_dimension = PixelDimension(0, 0);
}

Sprite::Sprite(const char* png_path, Screen* screen)
{
    int width, height;

    m_surface = IMG_Load(png_path);
    m_texture = SDL_CreateTextureFromSurface(screen->m_renderer, m_surface);
    SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);

    m_dimension.w = width;
    m_dimension.h = height;
}

void Sprite::render(PixelPosition position, Screen* screen)
{
    SDL_Rect dst_rect = {position.x, position.y, m_dimension.w, m_dimension.h};
    SDL_RenderCopy(screen->m_renderer, m_texture, NULL, &dst_rect);
}

Sprite::~Sprite(void)
{
    SDL_DestroyTexture(m_texture);
    SDL_FreeSurface(m_surface);

    std::cout << "freeing sprite" << std::endl;
}
