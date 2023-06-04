#ifndef STBIMAGE_H
#define STBIMAGE_H

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>
#include "Info.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

Info getTextureFromFile(const char *path, const std::string &directory, bool gamma = false);

unsigned int TextureToGPU(Info& info);

#endif // STBIMAGE_H
