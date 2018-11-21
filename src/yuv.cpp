#include "yuv.h"
#include "bitmap.h"
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
    return (width * height) * 1.5;
}

inline Vec3u YUV420Image::at(int x,int y) const
{
    Vec3u c;
    c[0] = *(_yPixels + y * _widthBytes[0] + x);
    c[1] = *(_uPixels + (y >> 1) * _widthBytes[1] + (x >> 1));
    c[2] = *(_vPixels + (y >> 1) * _widthBytes[2] + (x >> 1));
    return c;
}

inline Vec3u& YUV420Image::at(int x,int y)
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
    _uPixelsLength = static_cast<size_t>((_width * _height * 0.25)); 
    _vPixelsLength = _uPixelsLength;
    _yPixels = _pixels;
    _uPixels = _pixels  + _yPixelsLength;
    _vPixels = _uPixels + _uPixelsLength;
    _widthBytes[0] = _width;
    _widthBytes[1] = _width >> 1;
    _widthBytes[2] = _width >> 1;
}

inline static int clip(int value)
{
    return std::max(0, std::min(255, value));
}

ImagePtr YUV420Image::toBitmap() const
{
    BitmapImage *bitmap = new BitmapImage(_width, _height);
    uint8_t* const pBitmapData = bitmap->data();
    const size_t widthBytesOfBitmap = (bitmap->width() % 4 + bitmap->width() * 3);
    int C, D, E;
    uint8_t* p;
    for(int x = 0; x < _width; x++)
    {
        for(int y = 0; y < _height; y++)
        {
            const uint8_t &Y = *(_yPixels + y * _widthBytes[0] + x);
            const uint8_t &U = *(_uPixels + (y >> 1) * _widthBytes[1] + (x >> 1));
            const uint8_t &V = *(_vPixels + (y >> 1) * _widthBytes[2] + (x >> 1));
            C = Y - 16, D = U - 128, E = V - 128;
            p = pBitmapData + (_height - 1 - y) * widthBytesOfBitmap + (x << 1) + x;
            p[0] = clip((298 * C + 516 * D + 128) >> 8);
            p[1] = clip((298 * C + 409 * E + 128) >> 8);
            p[2] = clip((298 * C - 100 * D - 208 * E + 128) >> 8);
        }
    }
    return ImagePtr(bitmap);
}

