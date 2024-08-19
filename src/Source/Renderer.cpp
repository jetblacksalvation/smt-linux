#include "Renderer.hpp"
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <thread>
// Shader source code



RenderThread::RenderThread()
{
    this->_eventDispatcher = EventDispatcher(this->_window);
    this->InitWindow();
    this->InitOpenGL();
    this->StartGameLoop();
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
    glfwMakeContextCurrent(this->_window);
    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    std::cout << "GLAD initialized, version: " << version << std::endl;

    // Set the viewport
    glViewport(0, 0, 800, 600);
}

void RenderThread::InitOpenGL()
{
    const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

    const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // Change to red for testing
}
)";

    // Build and compile the shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link the shaders into a program
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and configure vertex attributes
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Left  
         0.5f, -0.5f, 0.0f,  // Right 
         0.0f,  0.5f, 0.0f   // Top   
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderThread::StartGameLoop()
{
    while (!glfwWindowShouldClose(this->_window)) {
        // Input
        if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(this->_window, true);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(_shaderProgram);

        // Bind the VAO
        glBindVertexArray(_VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(this->_window);

        // Poll for and process events
        glfwPollEvents();  // Ensure this is called to handle window events

        // Optional: Limit the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    // Cleanup
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteProgram(_shaderProgram);

    glfwDestroyWindow(_window);
    glfwTerminate();
}



RenderThread::~RenderThread() {
    if (not isThreadAlive) {
        EndGameLoop();
    }
}

void RenderThread::EndGameLoop()
{
    std::cout << "Ending game\n";
    isThreadAlive = false;
}
