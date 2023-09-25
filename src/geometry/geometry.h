#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
};

class Dimension
{
   public:
    int w;
    int h;

    Dimension(int w_ = 0, int h_ = 0)
    {
        w = w_;
        h = h_;
    }

    bool operator==(const Dimension& other) const;
};

class Position
{
   public:
    int x;
    int y;

    Position(int x_ = 0, int y_ = 0)
    {
        x = x_;
        y = y_;
    }

    bool operator==(const Position& other) const;
};

class TilePosition;
class PixelPosition;
class TileDimension;
class PixelDimension;

class TilePosition : public Position
{
   public:
    TilePosition(int w = 0, int h = 0) : Position(w, h) {}
    PixelPosition to_pixelwise(const PixelDimension tile_size);
};

class PixelPosition : public Position
{
   public:
    PixelPosition(int w = 0, int h = 0) : Position(w, h) {}
};

class TileDimension : public Dimension
{
   public:
    TileDimension(int w = 0, int h = 0) : Dimension(w, h) {}
};

class PixelDimension : public Dimension
{
   public:
    PixelDimension(int w = 0, int h = 0) : Dimension(w, h) {}
};

#endif
