#include "Renderer.hpp"
#include <thread>
#include <windows.h>

#include <iostream>

//init = { static_cast<OnInit::OnInitFuncT>(&Render::_InitRenderLoop) };
RenderThread::RenderThread() 
{

    this->_eventDispatcher  = EventDispatcher(this->_window);
    this->InitWindow();
    this->_gameRenderThread = std::thread(&RenderThread::StartGameLoop, this);

}
void RenderThread::InitWindow() 
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Set GLFW context version to 3.3 and use the core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    this->_window = glfwCreateWindow(800, 600, "Shin Megami Tensei", NULL, NULL);
    if (!this->_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(_window);

    // Initialize GLEW to setup the OpenGL function pointers
    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewInitResult) << std::endl;
        return;
    }


}
void RenderThread::StartGameLoop()
{

    while (!glfwWindowShouldClose(this->_window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(_window);

        // Poll for and process events
        glfwPollEvents();

        for (auto userDefinedEventFunc : this->_eventDispatcher.GetEventList())
        {
            userDefinedEventFunc(_window);
        }
    }
}
void RenderThread::EndGameLoop()
{
    this->_gameRenderThread.~thread();
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Render::_InitRenderLoop(OnInit* ptr)
{
    Render renderer;
    renderer.renderThread.StartGameLoop();

    // Terminate GLFW

}