#include "sprite.h"

Sprite::Sprite(const char* png_path, Screen* screen)
{
    int width, height;

    m_surface = IMG_Load(png_path);
    m_texture = SDL_CreateTextureFromSurface(screen->m_renderer, m_surface);
    SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);

    m_height = height;
    m_width = width;
}

void Sprite::render(int x, int y, Screen* screen)
{
    SDL_Rect dst_rect = {x, y, m_width, m_height};
    SDL_RenderCopy(screen->m_renderer, m_texture, NULL, &dst_rect);
}

Sprite::~Sprite(void)
{
    SDL_DestroyTexture(m_texture);
    SDL_FreeSurface(m_surface);
}
