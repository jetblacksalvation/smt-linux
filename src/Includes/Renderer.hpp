#ifndef RENDERER_SMT
#define RENDERER_SMT

#include "Common.hpp"
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
/*
	RenderLoop, start with .start method ,,
	Uses event binder

*/
class EventDispatcher
{
public:
	using EventDispatcherDelegate = std::function<void(GLFWwindow*)>;
	EventDispatcher():window(0), events({})
	{} 
	EventDispatcher(GLFWwindow* window) : window(window), events({})
	{
	}
	EventDispatcher(GLFWwindow* window, std::initializer_list<EventDispatcherDelegate> events) :window(window), events(events)
	{
	}

	//use copy constructor to change this ... 
private:
	GLFWwindow* window;
	std::vector< EventDispatcherDelegate> events;
};
class RenderThread
{
public:
	RenderThread();
	void StartGameLoop();
	void EndGameLoop();
private:
	void _InitWindow();
	EventDispatcher _eventDispatcher;
	GLFWwindow* _window;
	std::thread _gameRenderThread;
	//bool shoudRun = true;// just invoke kill function or break whatever
};

class RenderLoop
{
public:
	static void _InitRenderLoop(OnInit*);

private:

	static inline  OnInit RenderLoopInitializer = OnInit(_InitRenderLoop);
};

#endif // ! RENDERER_SMT