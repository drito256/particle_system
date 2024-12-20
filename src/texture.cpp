#include "../include/headers/texture.h"

Texture::Texture(const char* filepath){
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

/*    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

    this->data = stbi_load(filepath, &this->width, 
                           &this->height, &this->channels, 0);
    if(this->data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << width << "x" << height << std::endl;
    }
    else{
        std::cout << "Failed to load texture " << std::endl;
    }
}

int Texture::getID(){
    return this->id;
}
Texture::~Texture(){
    stbi_image_free(this->data);
}
