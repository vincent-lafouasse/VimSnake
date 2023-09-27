#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "geometry.h"
#include "render.h"
#include "snake.h"

#define TARGET_FPS 100
#define TILE_SIZE 30

#define GREEN_TILE_PNG "./assets/trex_pixel/snake_head_right.png"
#define BROWN_TILE_PNG "./assets/trex_pixel/snake_body.png"

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void)
{
    Screen screen = Screen(WIDTH, HEIGHT, TILE_SIZE);

    Sprite head_block = Sprite(GREEN_TILE_PNG, &screen);
    head_block.m_dimension = PixelDimension(TILE_SIZE, TILE_SIZE);

    Sprite body_block = Sprite(BROWN_TILE_PNG, &screen);
    body_block.m_dimension = PixelDimension(TILE_SIZE, TILE_SIZE);

    Snake snake = Snake(TilePosition(6, 9), &head_block, &body_block);

    SDL_Event event;
    uint32_t frame_beginning_tick;
    bool running = true;
    uint64_t frame_count = 1;

    // Chargement de l'image de fond
    SDL_Texture* backgroundTexture = IMG_LoadTexture(
        screen.m_renderer, "./assets/trex_pixel/background.png");
    if (!backgroundTexture)
    {
        fprintf(stderr, "Failed to load background image: %s\n",
                IMG_GetError());
        return EXIT_FAILURE;
    }

    while (running)
    {
        frame_beginning_tick = SDL_GetTicks();
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_h:
                        snake.set_direction(Direction::Left);
                        break;
                    case SDLK_j:
                        snake.set_direction(Direction::Down);
                        break;
                    case SDLK_k:
                        snake.set_direction(Direction::Up);
                        break;
                    case SDLK_l:
                        snake.set_direction(Direction::Right);
                        break;
                }
            }
        }

        if (frame_count % 50 == 0)
        {
            snake.advance();
        }

        Color::set_render_color(ColorID::NICE_BLUE, &screen);
        SDL_RenderClear(screen.m_renderer);

        snake.render(&screen);

        screen.show();

        cap_fps(frame_beginning_tick, TARGET_FPS);
        frame_count++;
    }

    // Libération de la texture de l'image de fond
    SDL_DestroyTexture(backgroundTexture);
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}

void cap_fps(uint32_t frame_beginning_tick, int target_fps)
{
    int ms_per_frame = 1000.0 / target_fps;
    uint32_t frame_end_tick = SDL_GetTicks();
    int time_to_wait = ms_per_frame - (frame_end_tick - frame_beginning_tick);

    if (time_to_wait > 0)
    {
        SDL_Delay(time_to_wait);
    }
}
