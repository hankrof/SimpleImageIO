#include "yuv.h"
#include <iostream>
YUV420Image::YUV420Image()
    : Image() ,_pixels(nullptr)
    ,_yPixels(nullptr) ,_uPixels(nullptr)
    ,_vPixels(nullptr) ,_pixelsLength(0) ,
    _yPixelsLength(0) ,_uPixelsLength(0) ,
    _vPixelsLength(0)
{
    
}

YUV420Image::YUV420Image(int width, int height)
    : Image(width, height)
{
    resize(width, height);
}

YUV420Image::YUV420Image(int width, int height, uint8_t *yuvPixels)
    : Image(width, height) ,_pixels(yuvPixels)
{
    determinePosAndStrides();
}

YUV420Image::~YUV420Image()
{
    delete[] _pixels; 
}

void YUV420Image::resize(int width, int height)
{
    try
    {
        delete[] _pixels;
        _width  = width;
        _height = height;
        _pixelsLength = pixelsLength(width, height);
        _pixels = new uint8_t[_pixelsLength];
        _yPixels = _pixels;
        _uPixels = _pixels + _width * height;
        _vPixels = _uPixels + static_cast<size_t>((_width * height * 1.0 / 4.0));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << "at BitmapImage::resize()" << std::endl;
        abort();
    }
   
}

uint32_t YUV420Image::pixelsLength() const
{
    return _pixelsLength; 
}

uint32_t YUV420Image::pixelsLength(int width, int height) const
{
    return (width * height) * 3.0 / 2.0;
}

Color YUV420Image::at(int x,int y) const
{
    //Y only currently.
    Color c;
    c.b = c.g = c.r = *(_yPixels + y * _width + x);
    return c;
}

Color& YUV420Image::at(int x,int y)
{
    _intermediateRefPixels[0] = (_yPixels + y * _width + x); 
    _intermediateRefPixels[1] = (_yPixels + y * _width + x); 
    _intermediateRefPixels[2] = (_yPixels + y * _width + x); 
    return *(_refColor = reinterpret_cast<Color*>(*_intermediateRefPixels));
}


uint8_t* YUV420Image::data()
{
   return _pixels; 
}

const uint8_t* YUV420Image::data() const
{
   return _pixels; 
}
 

void YUV420Image::determinePosAndStrides()
{
    _yPixelsLength = _width * _height;
    _uPixelsLength = static_cast<size_t>((_width * _height * 1.0 / 4.0)); 
    _vPixelsLength = _uPixelsLength;
    _yPixels = _pixels;
    _uPixels = _pixels  + _yPixelsLength;
    _vPixels = _uPixels + _uPixelsLength;
    _widthBytes[0] = _width;
    _widthBytes[1] = _width >> 1;
    _widthBytes[2] = _width >> 1;
}
