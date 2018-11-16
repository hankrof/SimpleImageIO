#include "imagewritter.h"
#include <iostream>
#include <fstream>
bool BitmapImageWritter::write(std::string filename, ImagePtr bitmap) const
{
    bool result = true;
    try
    {
        std::ofstream file(filename, std::ios::binary);
        if(!file.is_open())
            throw std::logic_error(std::string("Could not write file to [") + filename + "]");
        BitmapHeader header = makeHeader(bitmap);
        file.write(reinterpret_cast<char*>(&header), sizeof(BitmapHeader));
        file.write(reinterpret_cast<char*>(bitmap->data()), bitmap->pixelsLength());
        file.flush();
        if(file.tellp() != header.size)
            throw std::logic_error(std::string("Write to [") + filename + "] failed!");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << " at BitmapImageWritter::write()" << std::endl;
        result = false;
    }
    return result; 
}

BitmapHeader BitmapImageWritter::makeHeader(const ImagePtr bitmap) const
{
    BitmapHeader header;
    header.type[0]          = 'B';
    header.type[1]          = 'M';
    header.size             = bitmap->pixelsLength() + sizeof(BitmapHeader);
    header.reserved1        = 0;
    header.reserved2        = 0;
    header.bitmapDataOffset = sizeof(BitmapHeader);
    header.bitmapHeaderSize = 40;
    header.width            = static_cast<uint32_t>(bitmap->width());
    header.height           = static_cast<uint32_t>(bitmap->height());
    header.plane            = 1;
    header.bpp              = 24;
    header.compression      = 0;
    header.sizeImage        = header.size - sizeof(BitmapHeader);
    header.hResolution      = 0;
    header.vResolution      = 0;
    header.usedColors       = 0;
    header.importantColors  = 0;
    return header;
}
