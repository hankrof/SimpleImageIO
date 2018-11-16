#ifndef IMAEG_H
#define IMAEG_H
#include <stdint.h>
#include <cassert>
#include <exception>
#include <memory>
class Vec3u
{
public:
    Vec3u();
    Vec3u(uint8_t v1,uint8_t v2, uint8_t v3);
    uint8_t& operator[](int i);
    const uint8_t& operator[](int i) const;
    uint8_t v[3];
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
    virtual uint32_t pixelsLength() const = 0;
    virtual uint32_t pixelsLength(int width, int height) const = 0;
    virtual Vec3u  at(int x,int y) const = 0;
    virtual Vec3u& at(int x,int y) = 0;
    virtual uint8_t* data() = 0;
    virtual const uint8_t* data() const = 0;
protected:
    int _width, _height;
};
typedef std::shared_ptr<Image> ImagePtr;
#endif
