#ifndef YUV_H
#define YUV_H
#include "image.h"
class YUV420Image : public Image
{
public:
    YUV420Image();
    YUV420Image(int width, int height);
    YUV420Image(int width, int height, uint8_t *yuvPixels);
    ~YUV420Image();
    void resize(int width, int height);
    uint32_t pixelsLength() const;
    uint32_t pixelsLength(int width, int height) const;
    Vec3u  at(int x,int y) const;
    Vec3u& at(int x,int y);
    uint8_t* data();
    const uint8_t* data() const; 
private:
    void      determinePosAndStrides();
    Vec3u*   _refVec3u;
    int      _widthBytes[3];
    uint8_t* _intermediateRefPixels[3];
    uint8_t* _pixels;
    uint8_t* _yPixels;
    uint8_t* _uPixels;
    uint8_t* _vPixels;
    uint32_t _pixelsLength;
    uint32_t _yPixelsLength;
    uint32_t _uPixelsLength;
    uint32_t _vPixelsLength;
};

#endif
