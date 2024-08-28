#ifndef SHADERCOMMON_SMT
#define SHADERCOMMON_SMT
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream

#include "Renderer.hpp"
namespace ShaderCommon
{
    static GLuint compile_glsl_string(GLenum type, GLchar* const source)
    {
        GLuint shader;
        if (!source)
            return 0;

        shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        return shader;
    }
    static std::stringstream get_glsl_error(GLuint shaderid)
    {
        int success;
        char infoLog[512];
        std::stringstream ret; 
        glGetShaderiv(shaderid, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderid, 512, NULL, infoLog);
            ret<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return ret;
    }
}



#endif // !SHADERCOMMON_SMT
