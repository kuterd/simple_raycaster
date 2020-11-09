#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bitmap.h"

void BMP_initHeader(struct BMPHeader *header, long width, long height) {
    *header = (struct BMPHeader) {};
    header->signiture[0] = 'B';
    header->signiture[1] = 'M';
    header->data_offset = sizeof(struct BMPHeader);
    header->file_size = width * height * 4 + header->data_offset;

    header->size = 40;
    header->width = width;
    header->height = height;
    header->planes = 1;
    header->bits_per_pixel = 32;
    header->compression = 0;
    header->bitmap_size = width * height * 4;
//  header->cs_type = 1;
    header->x_ppm = 0;
    header->y_ppm = 0;

    header->colors_used = 0;
    header->colors_important = 0;
}



void bitmap_write(struct Bitmap bitmap, char *name) {
    FILE *file = fopen(name, "w");
    assert(file != NULL);
    
    struct BMPHeader header;
    BMP_initHeader(&header, bitmap.width, bitmap.height);

    fwrite(&header, sizeof(struct BMPHeader), 1, file);
    fwrite(bitmap.pixels, 4, bitmap.width * bitmap.height, file);
}

struct Bitmap bitmap_alloc(unsigned int width, unsigned int height) {
    unsigned int *pixels =
        (unsigned int*)malloc(width * height * sizeof(unsigned int));
    assert(pixels != NULL);

    return (struct Bitmap) {
        .width = width,
        .height = height,
        .pixels = pixels
    };
}
