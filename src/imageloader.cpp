#include "imageloader.h"
#include "bitmapheader.h"
#include <iostream>
bool ImageLoader::eof() const
{
    return true;
}

bool ImageLoader::setLoadingSize(int, int)
{
    throw std::string("Such loader do not support customized loading size.");
    return false;
}

ImagePtr BitmapImageLoader::read(const std::string filename) const
{
    BitmapHeader header;
    ImagePtr pImage;
    try
    {
        std::ifstream file(filename, std::ios::binary);
        if(!file.is_open())
            throw std::logic_error(std::string("Could not open file from [") + filename + "]");

        file.read(reinterpret_cast<char*>(&header), sizeof(BitmapHeader));

        if(header.type[0] != 'B' && header.type[1] != 'M')
            throw std::logic_error("Type in Bitmap Header are not equal to \'B\'M");

        if(header.bitmapDataOffset != sizeof(BitmapHeader))
            throw std::logic_error("Data Offset before pixels in Bitmap Header"
                                   " is not equal to Bitmap Header");
        if(header.size - sizeof(header) != 
            BitmapImage().pixelsLength(header.width, header.height))
            throw std::logic_error("Size image is not valid");

        if(header.bpp / 8 != 3)
            throw std::logic_error("Currently not works for gray image.");
        
        uint32_t len = header.size - sizeof(header);
        uint8_t *pixels = new uint8_t[len];
        file.read(reinterpret_cast<char*>(pixels), len);
        if(file.gcount() != len)
            throw std::logic_error("Bad image pixels data.");

        pImage.reset(new BitmapImage(header.width, header.height, pixels));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << " at BitmapImageLoader::read()" << std::endl;
    }
    return pImage; 
}


YUV420ImageLoader::YUV420ImageLoader()
    : _loadingWidth(0), _loadingHeight(0)
{

}

bool YUV420ImageLoader::eof() const
{
    return _file.eof();
}

ImagePtr YUV420ImageLoader::read(const std::string filename) const
{
    if(_file.is_open())
        return readNextFrame();
    _file.open(filename, std::ios::binary);
    if(!_file.is_open())
        throw std::logic_error(std::string("Could not open file from [") + filename + "]");
    return readNextFrame();
}

bool YUV420ImageLoader::setLoadingSize(int width, int height) 
{
    assert(width  > 0);
    assert(height > 0);
    _loadingWidth  = width;
    _loadingHeight = height;
    return true; 
}

ImagePtr YUV420ImageLoader::readNextFrame() const
{
    ImagePtr pImage;
    try
    {
        if(!_file.is_open())
            throw std::logic_error("File should be already opened");

        if(!_loadingWidth || !_loadingHeight)
            throw std::logic_error(std::string("Set the loading size before loading a yuv image!"));

        uint32_t len;
        uint8_t *yuvPlanarPixels = new uint8_t[len = YUV420Image().pixelsLength(_loadingWidth, _loadingHeight)];
        _file.read(reinterpret_cast<char*>(yuvPlanarPixels), len);
        pImage.reset(new YUV420Image(_loadingWidth, _loadingHeight, yuvPlanarPixels));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << " at YUV420ImageLoader::readNextFrame()" << std::endl;
    }
    return pImage;
}

