#include "bitmap.h"
#include "imageloader.h"
#include "imagewritter.h"
#include <iostream>

std::string takeFilename(const std::string &s)
{
    return s.substr(s.find_last_of('/') + 1);
}

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        std::cerr << "Usage ./program input.yuv width*height frame_num" << std::endl;
        std::cerr << "Ex ./program input.yuv 832*480 500"         << std::endl;
    }
    else
    {
        int width, height, frameNum;
        sscanf(argv[2], "%d*%d", &width, &height);
        sscanf(argv[3], "%d", &frameNum);
        assert(width > 0);
        assert(height > 0);
        ImageLoader  *loader  = new YUV420ImageLoader;
        ImageWritter *writter = new BitmapImageWritter;
        loader->setLoadingSize(width, height);
        ImagePtr image;
        std::string filename = takeFilename(argv[1]);
        for(int i = 0; i < frameNum && !loader->eof(); i++)
        {
            image = loader->read(argv[1]);
            writter->write(std::string(filename) + std::to_string(i) + ".bmp", image->toBitmap());
        }
    }
    return 0;
}

