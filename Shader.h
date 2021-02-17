#if !defined(SHADER_H)
#define SHADER_H

#include "Global.h"
#define MAX_SHADERS 3

struct Shader
{
    unsigned ID, shaders[MAX_SHADERS], linked;
    int success;
    char infoLog[512];

    Shader();
    void read(const char*, int);
    void link();
    void use();
    //setters
    void setBool(const char* name, bool value);
    void setInt(const char* name, int value);
    void setFloat(const char* name, float value);
    void setVectorFloat(const char* name, int count, float* value);
    void setVectorInt(const char* name, int count, int* value);
    ~Shader();
};
//SETTERS
inline void Shader::setBool(const char* name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
inline void Shader::setInt(const char* name, int value) {
    GL_DEBUG();
    int loc = glGetUniformLocation(ID, name);
    GL_DEBUG();
    PRINT("name: %s loc: %d\n",name, loc);
    GL_DEBUG();
    glUniform1i(loc, value);
    GL_DEBUG();
}
inline void Shader::setVectorFloat(const char* name, int count, float* value) {
    int loc = glGetUniformLocation(ID, name);
    PRINT("name: %s loc: %d count: %d\n",name, loc, count);
    glUniform1fv(loc, count, value);
}
inline void Shader::setVectorInt(const char* name, int count, int* value) {
    GL_DEBUG();
    int loc = glGetUniformLocation(ID, name);
    GL_DEBUG();
    PRINT("name: %s loc: %d count: %d\n",name, loc, count);
    GL_DEBUG();
    // DEBUGSHADER((*this));
    // GL_DEBUG();
    DEBUGARR(value, 32);
    glUniform1iv(loc, count, value);
    GL_DEBUG();
}
inline void Shader::setFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}

inline Shader::Shader():linked(0)
{
    ID = glCreateProgram();
}
void Shader::read(const char* filePath, int shaderEnum) {
    // 1. read
    std::string codeStr;
    std::ifstream shaderFile;
    std::stringstream fileStream;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        shaderFile.open(filePath);
        fileStream << shaderFile.rdbuf();		
        shaderFile.close();
        codeStr = fileStream.str();		
    }
    catch(std::ifstream::failure& e)
    {
        DEBUG(e.what());
    }
    const char* codeCharPtr = codeStr.c_str();
    
    // 2. compile
    
    shaders[linked] = glCreateShader(shaderEnum);
    glShaderSource(shaders[linked], 1, &codeCharPtr, NULL);
    glCompileShader(shaders[linked]);
    
    
    // print compile errors if any
    glGetShaderiv(shaders[linked], GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(shaders[linked], 512, NULL, infoLog);
        DEBUG("compilation failed");
    };
    glAttachShader(ID, shaders[linked]);
    ++linked;
    
}
void Shader::link() {
    
    glLinkProgram(ID);
    
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        DEBUG("shader linking failed");
    }
    
    for (unsigned i = 0; i < linked; ++i)
        glDeleteShader(shaders[i]);
    
}
inline void Shader::use() {
    glUseProgram(ID);
}
inline Shader::~Shader()
{
    glDeleteProgram(ID);
}


#endif // SHADER_H
