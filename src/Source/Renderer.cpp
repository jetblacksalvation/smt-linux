#include "Renderer.hpp"
#include <thread>
#include <windows.h>

#include <iostream>

//init = { static_cast<OnInit::OnInitFuncT>(&RenderLoop::_InitRenderLoop) };
RenderThread::RenderThread() 
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

    this->_eventDispatcher = EventDispatcher(this->_window);

}

void RenderLoop::_InitRenderLoop(OnInit* ptr)
{
    

    // Set the swap interval for the current context (1 means V-Sync is enabled)
    glfwSwapInterval(1);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}