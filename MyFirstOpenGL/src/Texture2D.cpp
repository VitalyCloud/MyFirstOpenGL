//
//  Texture2D.cpp
//  MyFirstOpenGL
//
//  Created by Vitaly Cloud on 04.02.2021.
//

#include "Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>

Texture2D::Texture2D() {
    mTexture = 0;
}
Texture2D::~Texture2D() {
    
}

bool Texture2D::loadTexture(const std::string& filename, bool generateMipMaps) {
    int width, height, components;
    
    /*
     stbi_load() will read the image
     from disk, allocate the memory for
     the array of bytes and return the pointer to that array
     */
    unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
    if (imageData == NULL) {
        std::cerr << "Error loading texture '" << filename << "'" << std::endl;
        return false;
    }
    
    //invert image by y axis
    int widthInBytes = width * 4;
    unsigned char *top = NULL;
    unsigned char *bottom = NULL;
    unsigned char temp = 0;
    int halfHeight = height / 2;
    for (int row=0; row<halfHeight; row++) {
        top = imageData + row * widthInBytes;
        bottom = imageData + (height - row - 1) * widthInBytes;
        for(int col = 0; col < widthInBytes; col++) {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }
    
    glGenTextures(1, &mTexture);
    
    //Bind texture to change parameters
    glBindTexture(GL_TEXTURE_2D, mTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //Pass image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    if(generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(imageData);
    
    //Unbind our texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture2D::bind(GLuint textureUnit) {
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
