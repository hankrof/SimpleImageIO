#include "image.h"
#include <memory.h>
Vec3u::Vec3u()
{
    memset(v, 0, sizeof(v));
}

Vec3u::Vec3u(uint8_t v1,uint8_t v2, uint8_t v3)
{
    v[0] = v1;
    v[1] = v2;
    v[2] = v3;
}

uint8_t& Vec3u::operator[](int i)
{
    return v[i];
}

const uint8_t& Vec3u::operator[](int i) const
{
    return v[i];
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
