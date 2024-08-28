#ifndef RENDERER_SMT
#define RENDERER_SMT

//#include "Common.hpp"
#include <thread>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <map>
#include <functional>
#include <vector>

/*
	RenderLoop, start with .start method,
	Uses event binder
*/
class EventDispatcher
{
public:
	using EventDispatcherDelegate = std::function<void(GLFWwindow*)>;

	EventDispatcher() : window(0), events({}) {}
	EventDispatcher(GLFWwindow* window) : window(window), events({}) {}
	EventDispatcher(GLFWwindow* window, std::initializer_list<EventDispatcherDelegate> events) : window(window), events(events) {}

	std::vector<EventDispatcherDelegate> GetEventList()
	{
		return events;
	}

	void AddNewEvent(EventDispatcherDelegate f)
	{
		this->events.push_back(f);
	}

private:
	GLFWwindow* window;
	std::vector<EventDispatcherDelegate> events;
};

class RenderThread
{
public:
	RenderThread();
	~RenderThread();
	void StartGameLoop();
	void EndGameLoop();
	void InitWindow();
	void InitOpenGL();  // New method to initialize OpenGL resources
	void AddEvent(EventDispatcher::EventDispatcherDelegate f)
	{
		_eventDispatcher.AddNewEvent(f);
	}

private:
	EventDispatcher _eventDispatcher;
	GLFWwindow* _window;
	bool isThreadAlive = true;  // Just invoke kill function or break whatever

	// OpenGL-related members
	unsigned int _VAO;          // Vertex Array Object
	unsigned int _VBO;          // Vertex Buffer Object
	unsigned int _shaderProgram; // Shader Program
};

class Render
{
public:
	static void InitRenderLoop();
	RenderThread renderThread;
};

#endif // !RENDERER_SMT
