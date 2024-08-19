#include "Renderer.hpp"
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
    // Create a windowed mode window and its OpenGL context

    this->_window = glfwCreateWindow(800, 600, "Shin Megami Tensei", NULL, NULL);
    if (!this->_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent(_window);
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }
}
void RenderThread::StartGameLoop()
{
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    

    while (!glfwWindowShouldClose(this->_window)) {
        // Clear the color buffer
        //glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers

        glClear(GL_COLOR_BUFFER_BIT);
        float* ptr = new float[2];
        glVertexAttribPointer(
            0,
            3,
            GL_INT,
            GL_FALSE,
            3 * 4,
            ptr
        );
        delete ptr;
        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();

        for (auto userDefinedEventFunc : this->_eventDispatcher.GetEventList())
        {
            std::cout << typeid(userDefinedEventFunc).name()<<"\n";
            userDefinedEventFunc(_window);
        }
    }
}
RenderThread::~RenderThread() {
    if (not isThreadAlive)
    {
        EndGameLoop();
    }
    else 
    {
        return;
        //dead anyways even if out of scope 
    }
}
void RenderThread::EndGameLoop()
{
    std::cout << "Ending game\n";
    this->_gameRenderThread.~thread();
    isThreadAlive = false;

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Render::InitRenderLoop()
{
    Render renderer;

    // Terminate GLFW

}