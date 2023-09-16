#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 600
#define WIDTH 800
#define TARGET_FPS 100

#define NICE_BLUE 33, 118, 174, 255

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} GameRenderer;

GameRenderer init_SDL(void) {
  GameRenderer game_renderer;
  const int SCREEN_X_POS = 0;
  const int SCREEN_Y_POS = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  game_renderer.window = SDL_CreateWindow(
      "a window", SCREEN_X_POS, SCREEN_Y_POS, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  if (game_renderer.window == NULL) {
    SDL_Log("Could not create a window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  game_renderer.renderer =
      SDL_CreateRenderer(game_renderer.window, -1, SDL_RENDERER_ACCELERATED);
  if (game_renderer.renderer == NULL) {
    SDL_Log("Could not create a renderer: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return game_renderer;
}

void destroy_game_renderer(GameRenderer game_renderer) {
  SDL_DestroyRenderer(game_renderer.renderer);
  SDL_DestroyWindow(game_renderer.window);
}

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void) {
  GameRenderer game_renderer = init_SDL();

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

    SDL_RenderPresent(game_renderer.renderer);

    cap_fps(frame_beginning_tick, TARGET_FPS);
  }

  destroy_game_renderer(game_renderer);
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
