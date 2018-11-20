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
        determinePosAndStrides();
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

Vec3u YUV420Image::at(int x,int y) const
{
    Vec3u c;
    c[0] = *(_yPixels + y * _widthBytes[0] + x);
    c[1] = *(_uPixels + (y >> 1) * _widthBytes[1] + (x >> 1));
    c[2] = *(_vPixels + (y >> 1) * _widthBytes[2] + (x >> 1));
    return c;
}

Vec3u& YUV420Image::at(int x,int y)
{
    _refVec3u = Vec3uRef(
                (_yPixels + y * _widthBytes[0] + x),
                (_uPixels + (y >> 1) * _widthBytes[1] + (x >> 1)),
                (_vPixels + (y >> 1) * _widthBytes[2] + (x >> 1))
            );
    return _refVec3u;
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
    _pixelsLength  = pixelsLength(_width, _height);
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
