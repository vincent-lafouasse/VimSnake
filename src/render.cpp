#include "render.h"

Screen init_renderer(void)
{
    Screen screen;
    const int SCREEN_X_POS = 0;
    const int SCREEN_Y_POS = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    screen.window = SDL_CreateWindow("a window", SCREEN_X_POS, SCREEN_Y_POS,
                                     WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (screen.window == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    screen.renderer =
        SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);
    if (screen.renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return screen;
}

void show(Screen screen)
{
    SDL_RenderPresent(screen.renderer);
}

void free_screen(Screen screen)
{
    SDL_DestroyRenderer(screen.renderer);
    SDL_DestroyWindow(screen.window);
}

Sprite sprite_from_png(const char* png_path, Screen screen)
{
    Sprite sprite;
    int width, height;

    sprite.surface = IMG_Load(png_path);
    sprite.texture =
        SDL_CreateTextureFromSurface(screen.renderer, sprite.surface);
    SDL_QueryTexture(sprite.texture, NULL, NULL, &width, &height);
    sprite.height = height;
    sprite.width = width;

    return sprite;
}

void render_sprite(Sprite sprite, int x, int y, Screen screen)
{
    SDL_Rect dst_rect = {x, y, sprite.width, sprite.height};
    SDL_RenderCopy(screen.renderer, sprite.texture, NULL, &dst_rect);
}

void free_sprite(Sprite sprite)
{
    SDL_DestroyTexture(sprite.texture);
    SDL_FreeSurface(sprite.surface);
}
