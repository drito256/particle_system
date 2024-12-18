#ifndef TEXTURE_H
#define TEXTURE_H

#include "../stb/stb_image.h"

#include <iostream>

class Texture{
    public:
        Texture(const char* filepath);
        ~Texture();

    private:
        const char* filepath;
        unsigned char* data;
        int width;
        int height;
        int channels;

};

#endif
