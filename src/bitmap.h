#ifndef BITMAP_H
#define BITMAP_H
#include "image.h"
class BitmapImage : public Image
{
public:
    BitmapImage();
    BitmapImage(int width, int height);
    BitmapImage(int width, int height, uint8_t *pixels);
    ~BitmapImage();
    void resize(int width, int height);
    uint32_t pixelsLength() const;
    uint32_t pixelsLength(int width, int height) const;
    Vec3u at(int x,int y) const;
    Vec3u& at(int x,int y);
    uint8_t* data();
    const uint8_t* data() const;
    ImagePtr toBitmap() const;
private:
    uint32_t widthBytes() const;
    uint32_t widthBytes(int width) const;
    uint32_t _widthBytes;
    uint8_t* _pixels;
    uint32_t _pixelsLength;
    Vec3u*   _refVec3u;
};
#endif
