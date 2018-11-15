#ifndef IMAEG_H
#define IMAEG_H
#include <stdint.h>
#include <cassert>
#include <exception>
#include <memory>
class Color
{
public:
    Color();
    Color(uint8_t r,uint8_t g, uint8_t b);
    uint8_t r, g, b;
};
class Image
{
public:
    Image();
    Image(int width, int height);
    virtual ~Image() = 0;
    int  width() const;
    int& width();
    int  height() const;
    int& height();
    virtual void resize(int width, int height) = 0;
    virtual uint32_t widthBytes() const = 0;
    virtual uint32_t widthBytes(int width) const = 0;
    virtual Color at(int x,int y) const = 0;
protected:
    int _width, _height;
};
typedef std::shared_ptr<Image> ImagePtr;
#endif
