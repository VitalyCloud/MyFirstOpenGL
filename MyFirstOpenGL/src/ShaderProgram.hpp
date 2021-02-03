//
//  ShaderProgram.hpp
//  MyFirstOpenGL
//
//  Created by Vitaly Cloud on 03.02.2021.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <string>

#include "GL/glew.h"

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    enum ShaderType {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };
    
    bool loadShaders(const char* vsFilename, const char* fsFilename);
    void use();

private:
    std::string fileToString(const std::string &filename);
    void checkCompileErrors(GLuint shader, ShaderType type);
    
    GLuint mHandle;
    
};

#endif /* ShaderProgram_hpp */
