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
        ImagePtr bitmap(new BitmapImage(width, height));
        std::string filename = takeFilename(argv[1]);
        for(int i = 0; i < frameNum && !loader->eof(); i++)
        {
            image = loader->read(argv[1]);
            for(int x = 0; x < image->width(); x++)
                for(int y = 0; y < image->height(); y++)
                {
                    Vec3u c = image->at(x, y); 
                    uint8_t &Y = c[0], &U = c[1], &V = c[2];
                    uint8_t b, g, r;
                    r = Y + 1.13983 * (V - 128);
                    g = Y - 0.39465 * (U - 128) - 0.58060 * (V - 128);
                    b = Y + 2.03211 * (U - 128);
                    bitmap->at(x, y) = Vec3u(b, g, r);
                }
            writter->write(std::string(filename) + std::to_string(i) + ".bmp", bitmap);
        }
    }
    return 0;
}

