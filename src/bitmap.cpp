#include "bitmap.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

BitmapImage::BitmapImage()
    : Image(), _widthBytes(0), 
     _pixels(nullptr)
{

}

BitmapImage::BitmapImage(int width, int height)
    : Image(width, height)
      , _widthBytes(widthBytes(width))
      , _pixels(nullptr)
      , _pixelsLength(pixelsLength(width, height))
{
    resize(width, height);
}

BitmapImage::BitmapImage(int width, int height, uint8_t *pixels)
    : Image(width, height)
      , _widthBytes(widthBytes(width))
      , _pixels(pixels)
      , _pixelsLength(pixelsLength(width, height))
{

}

BitmapImage::~BitmapImage()
{
    delete[] _pixels;
}

void BitmapImage::resize(int width, int height)
{
    try
    {
        delete[] _pixels;
        _width  = width;
        _height = height;
        _pixels = new uint8_t[_widthBytes * _height];
        _widthBytes = widthBytes(width);
        _pixelsLength = pixelsLength(width, height);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << "at BitmapImage::resize()" << std::endl;
        abort();
    }
}

uint32_t BitmapImage::widthBytes() const
{
    return _widthBytes;
}

uint32_t BitmapImage::widthBytes(int width) const
{
    return (width % 4) + width * 3;
}

uint32_t BitmapImage::pixelsLength() const
{
    return _pixelsLength;
}

uint32_t BitmapImage::pixelsLength(int width, int height) const
{
    return widthBytes(width) * height;
}

Color BitmapImage::at(int x,int y) const
{
    uint8_t* p = (_pixels + (_height - 1 - y) * _widthBytes + x * 3);
    return Color(p[2] , p[1], p[0]);
}

Color& BitmapImage::at(int x,int y)
{
    _refColor = reinterpret_cast<Color*>((_pixels + (_height - 1 - y) * _widthBytes + x * 3));
    return *_refColor;
}

uint8_t* BitmapImage::data()
{
    return _pixels;
}

const uint8_t* BitmapImage::data() const
{
    return _pixels;
}
