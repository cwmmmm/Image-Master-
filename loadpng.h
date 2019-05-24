#ifndef LOADPNG_H
#define LOADPNG_H

#include <iostream>
#include <vector>
#include "mymatrix.h"

std::vector<unsigned char> decodeOneStep(const char* filename, unsigned int *width, unsigned int *height);

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

Matrix *png_read(const char *filename);

void png_output(const char *filename, Matrix *input);

unsigned char *png_cache(Matrix *matrix);




#endif // LOADPNG_H
