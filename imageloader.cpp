#include "imageloader.h"
#include "bitmapheader.h"
#include <fstream>
#include <iostream>
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
            BitmapImage().widthBytes(header.width) * header.height)
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
        std::cerr << e.what() << " at BitmapImageLoader::open()" << std::endl;
    }
    return pImage; 
}


