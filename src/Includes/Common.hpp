#ifndef COMMON_SMT
#define COMMON_SMT

#include <functional>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
class OnInit
{
public:

	using OnInitFuncT = void(OnInit*);
	
	OnInit(OnInitFuncT);
	OnInit();
	void StartInit();
	static inline  Render renderer;

private:
	using OnInitFuncTWrapper = std::function<OnInitFuncT>;
	static inline std::vector<OnInitFuncTWrapper> InitList = {};
};
namespace Helpers
{
    static void show_info_log(
        GLuint object,
        PFNGLGETSHADERIVPROC glGet__iv,
        PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
    )
    {
        GLint log_length;
        char* log;

        glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
        log = (char*)malloc(log_length);
        glGet__InfoLog(object, log_length, NULL, log);
        fprintf(stderr, "%s", log);
        free(log);
    }
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

#endif // !COMMON_SMT