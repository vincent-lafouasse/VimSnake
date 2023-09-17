#ifndef __RENDER_H__
#define __RENDER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define HEIGHT 600
#define WIDTH 800

typedef struct {
  SDL_Window* window;
  SDL_Renderer* renderer;
} Screen;

Screen init_renderer(void);
void show(Screen screen);
void free_screen(Screen screen);

typedef struct {
  SDL_Surface* surface;
  SDL_Texture* texture;
  int width;
  int height;
} Sprite;

Sprite sprite_from_png(const char* png_path, Screen screen);
void render_sprite(Sprite sprite, int x, int y, Screen screen);
void free_sprite(Sprite sprite);

#endif
