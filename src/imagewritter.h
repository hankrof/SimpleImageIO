#ifndef IMAGEWRITTER_H
#define IMAGEWRITTER_H
#include "bitmap.h"
#include "bitmapheader.h"
#include <string>
class ImageWritter
{
public:
    virtual bool write(std::string filename, ImagePtr image) const = 0;
};
class BitmapImageWritter
{
public:
    bool write(std::string filename, ImagePtr bitmap) const;
private:
    BitmapHeader makeHeader(const ImagePtr bitmap) const;
};
#endif
