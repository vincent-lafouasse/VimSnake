#include "geometry.h"

PixelPosition TilePosition::to_pixelwise(const PixelDimension tile_size)
{
    return PixelPosition(x * tile_size.w, y * tile_size.h);
}

bool Dimension::operator==(const Dimension& other) const
{
    return (w == other.w) && (h == other.h);
}

bool Position::operator==(const Position& other) const
{
    return (x == other.x) && (y == other.y);
}
