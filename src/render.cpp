#include "render.h"

GameRenderer init_renderer(void)
{
    GameRenderer game_renderer;
    const int SCREEN_X_POS = 0;
    const int SCREEN_Y_POS = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    game_renderer.window =
        SDL_CreateWindow("a window", SCREEN_X_POS, SCREEN_Y_POS, WIDTH, HEIGHT,
                         SDL_WINDOW_OPENGL);
    if (game_renderer.window == NULL)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    game_renderer.renderer =
        SDL_CreateRenderer(game_renderer.window, -1, SDL_RENDERER_ACCELERATED);
    if (game_renderer.renderer == NULL)
    {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return game_renderer;
}

void show(GameRenderer game_renderer)
{
    SDL_RenderPresent(game_renderer.renderer);
}

void free_game_renderer(GameRenderer game_renderer)
{
    SDL_DestroyRenderer(game_renderer.renderer);
    SDL_DestroyWindow(game_renderer.window);
}

Sprite sprite_from_png(const char* png_path, GameRenderer game_renderer)
{
    Sprite sprite;
    int width, height;

    sprite.surface = IMG_Load(png_path);
    sprite.texture =
        SDL_CreateTextureFromSurface(game_renderer.renderer, sprite.surface);
    SDL_QueryTexture(sprite.texture, NULL, NULL, &width, &height);
    sprite.height = height;
    sprite.width = width;

    return sprite;
}

void render_sprite(Sprite sprite, int x, int y, GameRenderer game_renderer)
{
    SDL_Rect dst_rect = {x, y, sprite.width, sprite.height};
    SDL_RenderCopy(game_renderer.renderer, sprite.texture, NULL, &dst_rect);
}

void free_sprite(Sprite sprite)
{
    SDL_DestroyTexture(sprite.texture);
    SDL_FreeSurface(sprite.surface);
}
