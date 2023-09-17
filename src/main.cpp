#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "render.h"
#include "snake.h"

#define TARGET_FPS 100

#define NICE_BLUE 33, 118, 174, 255

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void)
{
    Screen screen = Screen(WIDTH, HEIGHT);

    Sprite crab = Sprite("assets/crab.png", &screen);

    Snake snake = Snake(TilePosition(0, 0), &crab);

    const PixelDimension grid_size = crab.m_dimension;

    SDL_Event event;
    uint32_t frame_beginning_tick;
    bool running = true;

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
        }

        SDL_SetRenderDrawColor(screen.m_renderer, NICE_BLUE);
        SDL_RenderClear(screen.m_renderer);

        snake.render(&screen, grid_size);

        screen.show();

        cap_fps(frame_beginning_tick, TARGET_FPS);
    }

    SDL_Quit();
    return (EXIT_SUCCESS);
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
