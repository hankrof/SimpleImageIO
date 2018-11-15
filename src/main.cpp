#include "bitmap.h"
#include "imageloader.h"
#include "imagewritter.h"
#include <iostream>
int main(int argc, char **argv)
{
    if(argc != 3)
        std::cerr << "Usage ./program input.bmp output.bmp" << std::endl;
    else
    {
        ImageLoader *loader = new BitmapImageLoader;
        ImageWritter *writter = new BitmapImageWritter;
        ImagePtr image = loader->read(argv[1]);
        writter->write(argv[2], image);        
    }
    return 0;
}

