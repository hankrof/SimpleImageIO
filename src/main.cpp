#include "bitmap.h"
#include "imageloader.h"
#include "imagewritter.h"
#include <iostream>
int main(void)
{
    ImageLoader *loader = new BitmapImageLoader();
    //BitmapImageLoader  loader;
    BitmapImageWritter writter;
    ImagePtr image = loader->read("pic/test2.bmp");
    writter.write("pic/copy.bmp", image);
    return 0;
}

