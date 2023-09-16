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
  SDL_Window* window;
  SDL_Renderer* renderer;
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

void free_game_renderer(GameRenderer game_renderer) {
  SDL_DestroyRenderer(game_renderer.renderer);
  SDL_DestroyWindow(game_renderer.window);
}

typedef struct {
  SDL_Surface* surface;
  SDL_Texture* texture;
  int width;
  int height;
} Sprite;

Sprite sprite_from_png(const char* png_path, GameRenderer game_renderer) {
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

void render_sprite(Sprite sprite, int x, int y, GameRenderer game_renderer) {
  SDL_Rect dst_rect = {x, y, sprite.width, sprite.height};
  SDL_RenderCopy(game_renderer.renderer, sprite.texture, NULL, &dst_rect);
}

void free_sprite(Sprite sprite) {
  SDL_DestroyTexture(sprite.texture);
  SDL_FreeSurface(sprite.surface);
}

void cap_fps(uint32_t frame_beginning_tick, int target_fps);

int main(void) {
  GameRenderer game_renderer = init_SDL();

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

    SDL_RenderPresent(game_renderer.renderer);

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
