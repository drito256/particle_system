#include "../include/headers/texture.h"


Texture::Texture(const char* filepath){
    this->data = stbi_load(filepath, &this->width, 
                           &this->height, &this->channels, 0);
}

Texture::~Texture(){
    stbi_image_free(this->data);
}
