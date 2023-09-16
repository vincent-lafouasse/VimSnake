
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "render.h"

#define TARGET_FPS 100

#define NICE_BLUE 33, 118, 174, 255

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void) {
  GameRenderer game_renderer = init_renderer();

  Sprite crab = sprite_from_png("src/crab.png", game_renderer);

  SDL_Event event;
  uint32_t frame_beginning_tick;
  bool running = true;

  while (running) {
    frame_beginning_tick = SDL_GetTicks();
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      }
    }

    SDL_SetRenderDrawColor(game_renderer.renderer, NICE_BLUE);
    SDL_RenderClear(game_renderer.renderer);

    render_sprite(crab, 0, 0, game_renderer);

    show(game_renderer);

    cap_fps(frame_beginning_tick, TARGET_FPS);
  }

  free_sprite(crab);
  free_game_renderer(game_renderer);
  SDL_Quit();
  return (EXIT_SUCCESS);
}

void cap_fps(uint32_t frame_beginning_tick, int target_fps) {
  int ms_per_frame = 1000.0 / target_fps;
  uint32_t frame_end_tick = SDL_GetTicks();
  int time_to_wait = ms_per_frame - (frame_end_tick - frame_beginning_tick);

  if (time_to_wait > 0) {
    SDL_Delay(time_to_wait);
  }
}
