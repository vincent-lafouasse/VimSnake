#pragma once

#include "render.h"

enum class ColorID
{
    NICE_BLUE,
};

struct RGBA
{
    RGBA(int r_, int g_, int b_, int a_);
    static RGBA get(ColorID id);

    int r;
    int g;
    int b;
    int a;
};

namespace Color
{
void set_render_color(ColorID id, Screen* screen);
}
