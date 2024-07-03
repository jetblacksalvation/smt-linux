#ifndef GAME_SMT
#define GAME_SMT
#include <iostream>
#include "Common.hpp"
class TriangleRenderer 
{


	static void RenderTriangle(OnInit * ptr)
	{
		std::cout << "Done Rendering\n";

		EventDispatcher::EventDispatcherDelegate _RenderTriangle = [](GLFWwindow*)
			{
				float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
				};
				unsigned int VBO;
				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


			};
		ptr->renderer.renderThread.AddEvent(_RenderTriangle);
	};

	static inline  OnInit TriangleRender = OnInit(RenderTriangle);
};



#endif // !GAME_SMT


