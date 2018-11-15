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
{
    resize(width, height);
}

BitmapImage::BitmapImage(int width, int height, uint8_t *pixels)
    : Image(width, height)
      , _widthBytes(widthBytes(width))
      , _pixels(pixels)
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

Color BitmapImage::at(int x,int y) const
{
    uint8_t* p = (_pixels + y * _widthBytes + x * 3);
    return Color(p[2] , p[1], p[0]);
}

