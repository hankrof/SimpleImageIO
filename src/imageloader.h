#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include "bitmap.h"
#include <memory>
class ImageLoader
{
public:
    virtual ImagePtr read(const std::string filename) const = 0;
};
class BitmapImageLoader : public ImageLoader
{
public:
    ImagePtr read(const std::string filename) const;
};
#endif
