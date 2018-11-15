#include "bitmap.h"
#include "imageloader.h"
#include "imagewritter.h"
#include <iostream>
int main(void)
{
    BitmapImageLoader  loader;
    BitmapImageWritter writter;
    ImagePtr image = loader.read("pic/test4.bmp");
    writter.write("pic/copy.bmp", image);
    return 0;
}

