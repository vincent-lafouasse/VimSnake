#include "geometry.h"

Direction opposite_direction(Direction direction)
{
    switch (direction)
    {
        case Direction::Up:
            return Direction::Down;
        case Direction::Down:
            return Direction::Up;
        case Direction::Left:
            return Direction::Right;
        case Direction::Right:
            return Direction::Left;
    }
}

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

TilePosition TilePosition::operator+(const TilePosition& other) const
{
    return TilePosition(x + other.x, y + other.y);
}
TilePosition TilePosition::operator-(const TilePosition& other) const
{
    return TilePosition(x - other.x, y - other.y);
}
