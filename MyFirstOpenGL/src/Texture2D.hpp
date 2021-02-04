//
//  Texture2D.hpp
//  MyFirstOpenGL
//
//  Created by Vitaly Cloud on 04.02.2021.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include "GL/glew.h"

#include <stdio.h>
#include <string>


class Texture2D {
public:
    Texture2D();
    virtual ~Texture2D();
    
    bool loadTexture(const std::string& filename, bool generateMipMaps = true);
    void bind(GLuint textureUnit = 0);
    
private:
    GLuint mTexture;
};

#endif /* Texture2D_hpp */
