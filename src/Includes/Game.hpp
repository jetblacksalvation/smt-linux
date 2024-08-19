#ifndef GAME_SMT
#define GAME_SMT
#include <iostream>
#include "Common.hpp"
#include "Renderer.hpp"
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

class TriangleRenderer 
{
    static inline EventDispatcher::EventDispatcherDelegate _RenderTriangle = [](GLFWwindow* window) 
	{

		std::cout << "Rendering Triangle\n";
    };


	static void RenderTriangle(OnInit * ptr)
	{
		
		ptr->renderer.renderThread.AddEvent(_RenderTriangle);
	};

	static inline OnInit TriangleRender = OnInit(RenderTriangle);
};



#endif // !GAME_SMT


