#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include "bitmap.h"
#include "yuv.h"
#include <memory>
#include <fstream>
class ImageLoader
{
public:
    virtual ImagePtr read(const std::string filename = "") const = 0;
    virtual bool eof() const;
    virtual bool setLoadingSize(int width, int height);
};

class BitmapImageLoader : public ImageLoader
{
public:
    ImagePtr read(const std::string filename) const;
};

class YUV420ImageLoader : public ImageLoader
{
public:
    YUV420ImageLoader();
    bool eof() const;
    ImagePtr read(const std::string filename) const;
    bool setLoadingSize(int width, int height);
private:
    ImagePtr readNextFrame() const;
    int _loadingWidth, _loadingHeight;
    mutable std::ifstream _file;
};
#endif
