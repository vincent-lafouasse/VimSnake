#include "color.h"
#include "render.h"

#define NICE_BLUE_RGBA 45, 38, 62, 255

namespace Color
{
void set_render_color(ColorID id, Screen* screen)
{
    RGBA rgba = RGBA::get(id);
    SDL_SetRenderDrawColor(screen->m_renderer, rgba.r, rgba.g, rgba.b, rgba.a);
}
}  // namespace Color

RGBA RGBA::get(ColorID id)
{
    switch (id)
    {
        case ColorID::NICE_BLUE:
            return RGBA(NICE_BLUE_RGBA);
    }
}

RGBA::RGBA(int r_, int g_, int b_, int a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
}
