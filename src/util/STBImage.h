#ifndef STBIMAGE_H
#define STBIMAGE_H

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

#endif // STBIMAGE_H
