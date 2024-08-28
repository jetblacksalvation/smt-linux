#ifndef SHADERCOMMON_SMT
#define SHADERCOMMON_SMT
namespace ShaderCommon
{
    static GLuint compile_glsl_string(GLenum type, GLchar* const source)
    {
        GLint length = std::string((char*)source).size();


        GLuint shader;
        GLint shader_ok;
        if (!source)
            return 0;

        shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, &length);
        glCompileShader(shader);
    }
}



#endif // !SHADERCOMMON_SMT
