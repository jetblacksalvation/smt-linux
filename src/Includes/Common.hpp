#ifndef COMMON_SMT
#define COMMON_SMT

#include <functional>
#include <vector>
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
    static void show_info_lo(
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


}

#endif // !COMMON_SMT