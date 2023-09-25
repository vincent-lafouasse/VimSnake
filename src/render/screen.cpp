#include "screen.h"
#include <iostream>

Screen::Screen(int width, int height, int tile_size)
{
    const int SCREEN_X_POS = 0;
    const int SCREEN_Y_POS = 0;

	m_tile_size = tile_size;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    m_window = SDL_CreateWindow("a window", SCREEN_X_POS, SCREEN_Y_POS, width,
                                height, SDL_WINDOW_OPENGL);
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
