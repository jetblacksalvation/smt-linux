#ifndef GAME_SMT
#define GAME_SMT
#include <iostream>
#include "Common.hpp"
class TriangleRenderer 
{
	static inline EventDispatcher::EventDispatcherDelegate _RenderTriangle = [](GLFWwindow*)
		{
			static const GLchar* vertexShaderSource = R"(
				#version 110

				attribute vec2 position;

				varying vec2 texcoord;

				void main()
				{
					gl_Position = vec4(position, 0.0, 1.0);
					texcoord = position * vec2(0.5) + vec2(0.5);
				}

				})";
			static const GLchar * fragmentShader = R"(
				#version 110

				uniform float fade_factor;
				uniform sampler2D textures[2];

				varying vec2 texcoord;

				void main()
				{
					gl_FragColor = mix(
						texture2D(textures[0], texcoord),
						texture2D(textures[1], texcoord),
						fade_factor
					);
				}
				)";
			GLuint shader1 = Helpers::compile_glsl_string(GL_VERTEX_SHADER, (GLchar*)vertexShaderSource);
			GLuint shader2 = Helpers::compile_glsl_string(GL_FRAGMENT_SHADER, (GLchar*)fragmentShader);
			GLint program_ok;

			GLuint program = glCreateProgram();
			glAttachShader(program, shader1);
			glAttachShader(program, shader2);
			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
			if (!program_ok) {
				fprintf(stderr, "Failed to link shader program:\n");
				Helpers::show_info_log(program, glGetProgramiv, glGetProgramInfoLog);
				glDeleteProgram(program);
			}
			glUseProgram(program);
			auto fade_factor
				= glGetUniformLocation(program, "fade_factor");
			auto textures = { glGetUniformLocation(program, "textures[0]"),glGetUniformLocation(program, "textures[1]") };

			auto position
				= glGetAttribLocation(program, "position");
			glUniform1f(fade_factor, fade_factor);
		};

	static void RenderTriangle(OnInit * ptr)
	{
		
		ptr->renderer.renderThread.AddEvent(_RenderTriangle);
	};

	static inline OnInit TriangleRender = OnInit(RenderTriangle);
};



#endif // !GAME_SMT


