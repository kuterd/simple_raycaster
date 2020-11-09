#ifndef BITMAP_H
#define BITMAP_H

#pragma pack(push, 1)
struct BMPHeader {
    char signiture[2]; // = "BM"
    unsigned int file_size;
    char res[4];
    unsigned int data_offset;
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int bitmap_size;
    int x_ppm;
    int y_ppm;
    unsigned int colors_used;
    unsigned int colors_important;
};
#pragma pack(pop)

void BMP_initHeader(struct BMPHeader *header, long width, long height);

struct Bitmap {
    unsigned int width;
    unsigned int height;
    unsigned int *pixels;
};
struct Bitmap bitmap_alloc(unsigned int width, unsigned int height);
void bitmap_write(struct Bitmap bitmap, char *name);

#endif
