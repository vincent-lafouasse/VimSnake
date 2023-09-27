#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "geometry.h"
#include "render.h"
#include "snake.h"
#include "snake_renderer.h"

#define TARGET_FPS 100
#define TILE_SIZE 50

#define FRAMES_PER_TICK 50

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void)
{
    Screen screen(WIDTH, HEIGHT, TILE_SIZE);

    SnakeRenderer snake_renderer(&screen);
    Snake snake(TilePosition(6, 9));

    SDL_Event event;
    uint32_t frame_beginning_tick;
    bool running = true;
    uint64_t frame_count = 0;

    while (running && ++frame_count)
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

        if (frame_count % FRAMES_PER_TICK == 0)
        {
            snake.advance();
        }

        Color::set_render_color(ColorID::NICE_BLUE, &screen);
        SDL_RenderClear(screen.m_renderer);

        snake_renderer.render(&snake, &screen);

        screen.show();

        cap_fps(frame_beginning_tick, TARGET_FPS);
    }

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
