#include "geometry.h"

bool Dimension::operator==(const Dimension& other) const
{
    return (w == other.w) && (h == other.h);
}

bool Position::operator==(const Position& other) const
{
    return (x == other.x) && (y == other.y);
}
