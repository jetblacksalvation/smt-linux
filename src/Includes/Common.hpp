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

#endif // !COMMON_SMT