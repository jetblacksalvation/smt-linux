#ifndef RENDERER_SMT
#define RENDERER_SMT

//#include "Common.hpp"
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <functional>

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
	std::vector<EventDispatcherDelegate> GetEventList()
	{
		return events;
	}
	void AddNewEvent(EventDispatcherDelegate f)
	{
		this->events.push_back(f);
	}
	//use copy constructor to change this ... 
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
	void AddEvent(EventDispatcher::EventDispatcherDelegate f)
	{
		_eventDispatcher.AddNewEvent(f);
	}
private:
	EventDispatcher _eventDispatcher;
	GLFWwindow* _window;
	std::thread _gameRenderThread;
	bool isThreadAlive = true;// just invoke kill function or break whatever
};


class Render
{
public:
	static void InitRenderLoop();
	RenderThread renderThread; 
	//static inline  OnInit RenderLoopInitializer = OnInit(_InitRenderLoop);
};

#endif // ! RENDERER_SMT
