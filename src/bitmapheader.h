#ifndef BITMAPHEADER_H
#define BITMAPHEADER_H
#include <stdint.h>
class BitmapHeader
{
public:
    char     type[2];
    uint32_t size; 
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bitmapDataOffset;
    uint32_t bitmapHeaderSize;
    uint32_t width;
    uint32_t height;
    uint16_t plane;
    uint16_t bpp;
    uint32_t compression;
    uint32_t sizeImage;
    uint32_t hResolution;
    uint32_t vResolution;
    uint32_t usedColors;
    uint32_t importantColors;
} __attribute__((packed));
#endif
