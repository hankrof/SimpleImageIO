#ifndef YUV_H
#define YUV_H
#include "image.h"
/*
    virtual void resize(int width, int height) = 0;
    virtual uint32_t pixelsLength() const = 0;
    virtual uint32_t pixelsLength(int width, int height) const = 0;
    virtual Color at(int x,int y) const = 0;
    virtual uint8_t* data() = 0;
    virtual const uint8_t* data() const = 0; 
*/
class YUV420Image : public Image
{
public:
    YUV420Image();
    YUV420Image(int width, int height);
    ~YUV420Image();
    void resize(int width, int height);
    uint32_t pixelsLength() const;
    uint32_t pixelsLength(int width, int height) const;
    Color at(int x,int y) const;
    uint8_t* data();
    const uint8_t* data() const; 
private:
    uint8_t*  _pixels;
    uint8_t*& _yPixels;
    uint8_t*& _uPixels;
    uint8_t*& _vPixels;
};

#endif
