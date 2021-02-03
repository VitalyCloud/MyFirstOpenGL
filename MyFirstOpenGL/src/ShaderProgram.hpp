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
#include <map>

#include "GL/glew.h"
#include "glm/glm.hpp"

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
    
    void setUniform(const GLchar *name, const glm::vec2& v);
    void setUniform(const GLchar *name, const glm::vec3& v);
    void setUniform(const GLchar *name, const glm::vec4& v);

private:
    std::string fileToString(const std::string &filename);
    void checkCompileErrors(GLuint shader, ShaderType type);
    GLuint getUniformLocation(const GLchar *name);
    
    GLuint mHandle;
    std::map<std::string, GLuint> mUniformLocations;
};

#endif /* ShaderProgram_hpp */
