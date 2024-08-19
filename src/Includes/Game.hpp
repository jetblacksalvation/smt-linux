#ifndef GAME_SMT
#define GAME_SMT
#include <iostream>
#include "Common.hpp"
class TriangleRenderer 
{
    static inline EventDispatcher::EventDispatcherDelegate _RenderTriangle = [](GLFWwindow* window) {
        std::cout << "Rendering Triangle\n";
        };


	static void RenderTriangle(OnInit * ptr)
	{
		
		ptr->renderer.renderThread.AddEvent(_RenderTriangle);
	};

	static inline OnInit TriangleRender = OnInit(RenderTriangle);
};



#endif // !GAME_SMT


