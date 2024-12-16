#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

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
