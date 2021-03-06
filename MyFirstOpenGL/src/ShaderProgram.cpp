//
//  ShaderProgram.cpp
//  MyFirstOpenGL
//
//  Created by Vitaly Cloud on 03.02.2021.
//

#include "ShaderProgram.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram() {
    mHandle = 0;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(mHandle);
}

bool ShaderProgram::loadShaders(const char *vsFilename, const char *fsFilename) {
    
    std::string vsString = fileToString(vsFilename);
    std::string fsString = fileToString(fsFilename);
    const GLchar* vsSourcePtr = vsString.c_str();
    const GLchar* fsSourcePtr = fsString.c_str();
    
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSourcePtr, NULL);
    glShaderSource(fs, 1, &fsSourcePtr, NULL);
    
    glCompileShader(vs);
    checkCompileErrors(vs, VERTEX);
    
    glCompileShader(fs);
    checkCompileErrors(vs, FRAGMENT);
    
    
    
    //Create programm
    mHandle = glCreateProgram();
    glAttachShader(mHandle, vs);
    glAttachShader(mHandle, fs);
    glLinkProgram(mHandle);
    
    checkCompileErrors(mHandle, PROGRAM);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    mUniformLocations.clear();
    
    return true;
}

void ShaderProgram::use() {
    if(mHandle > 0)
        glUseProgram(mHandle);
}

std::string ShaderProgram::fileToString(const std::string &filename) {
    std::stringstream ss;
    std::ifstream file;
    
    try {
        file.open(filename, std::ios::in);
        if(!file.fail()) {
            ss << file.rdbuf();
        }
        file.close();
    }
    catch (std::exception ex) {
        std::cerr << "Error reading shader filename!" << std::endl;
    }
    return ss.str();
}

void ShaderProgram::checkCompileErrors(GLuint shader, ShaderType type) {
    int status = 0;
    if(type == PROGRAM) {
        glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);
            
            std::string errorLog(length, ' ');
            glGetProgramInfoLog(mHandle, length, &length, &errorLog[0]);
            std::cerr << "Error! Program faied to link." << errorLog << std::endl;
        }
    } else { // VERTEX or FRAGMENT
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            
            std::string errorLog(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader faied to compile." << errorLog << std::endl;
        }
    }
}

GLuint ShaderProgram::getUniformLocation(const GLchar *name) {
    std::map<std::string, GLuint>::iterator it = mUniformLocations.find(name);
    
    if(it == mUniformLocations.end()) {
        mUniformLocations[name] = glGetUniformLocation(mHandle, name);
    }
    
    return mUniformLocations[name];
}
     
void ShaderProgram::setUniform(const GLchar *name, const glm::vec2& v) {
    GLint loc = getUniformLocation(name);
    glUniform2f(loc, v.x, v.y);
}

void ShaderProgram::setUniform(const GLchar *name, const glm::vec3& v) {
    GLint loc = getUniformLocation(name);
    glUniform3f(loc, v.x, v.y, v.z);
}

void ShaderProgram::setUniform(const GLchar *name, const glm::vec4& v) {
    GLint loc = getUniformLocation(name);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}
