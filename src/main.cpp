#include "bitmap.h"
#include "imageloader.h"
#include "imagewritter.h"
#include <iostream>
int main(int argc, char **argv)
{
    if(argc != 3)
        std::cerr << "Usage ./program input.yuv output_name" << std::endl;
    else
    {
        ImageLoader  *loader  = new YUV420ImageLoader;
        ImageWritter *writter = new BitmapImageWritter;
        loader->setLoadingSize(832, 480);
        ImagePtr image;
        ImagePtr bitmap(new BitmapImage(832, 480));
        int cnt = 0;
        while(!loader->eof())
        {
            image = loader->read(argv[1]);
            for(int x = 0; x < image->width(); x++)
                for(int y = 0; y < image->height(); y++)
                    bitmap->at(x, y) = image->at(x, y);
            writter->write(std::to_string(++cnt) + argv[2], bitmap);
        }
    }
    return 0;
}

