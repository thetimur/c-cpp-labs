#ifndef BMP_H
#define BMP_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

#pragma pack(push,1)

struct Header {
	int16_t signature;
	int32_t file_size;
	int16_t res1, res2;
	int32_t file_offset;
};

struct DIB_Header {
	int32_t header_size;
	int32_t width;
	int32_t height;
	int16_t planes;
	int16_t bit_count;	
	int32_t compression;
	int32_t image_size;
	int32_t other[4];
};

struct Color {
	char red;
	char green;
	char blue;
};

#pragma pack(pop)

typedef struct Header Header_t;
typedef struct DIB_Header DIB_Header_t;
typedef struct Color Color_t;

struct BMP {
	Header_t header;
	DIB_Header_t DIB;
	Color_t **data;	
};

typedef struct BMP BMP_t;

int load_bmp(FILE* in, BMP_t *image);
int save_bmp(FILE* out, BMP_t *image);
BMP_t rotate(BMP_t *image, int *status);
BMP_t crop(BMP_t *image, int *status, int x, int y, int w, int h);
int get_padding_size(int val);

#endif //BMP_H