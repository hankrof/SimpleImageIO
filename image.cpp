#include "image.h"
Color::Color()
    : r(0), g(0), b(0)
{

}

Color::Color(uint8_t r,uint8_t g, uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Image::Image()
    : _width(0), _height(0)
{

}

Image::~Image()
{

}

Image::Image(int width, int height)
    : _width(width), _height(height)
{
    assert(width  > 0);
    assert(height > 0);
}

int  Image::width() const
{
    return _width;
}

int& Image::width()
{
    return _width;
}

int  Image::height() const
{
    return _height;
}

int& Image::height()
{
    return _height;
}
