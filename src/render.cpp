#include "render.h"

#include <iostream>

Screen::Screen(void)
{
    const int SCREEN_X_POS = 0;
    const int SCREEN_Y_POS = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    m_window = SDL_CreateWindow("a window", SCREEN_X_POS, SCREEN_Y_POS, WIDTH,
                                HEIGHT, SDL_WINDOW_OPENGL);
    if (m_window == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Screen::show(void)
{
    SDL_RenderPresent(m_renderer);
}

Screen::~Screen(void)
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    std::cout << "deleting screen" << std::endl;
}

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
