#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"

GLfloat points[] =
{
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.5f
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertexShader =
"#version 460\n"
"layout(location = 0) in vec3 vertexPosition;"
"layout(location = 1) in vec3 vertexColor;"
"out vec3 color;"
"void main() {"
"   color = vertexColor;"
"   gl_Position = vec4(vertexPosition, 1.0f);"
"}";

const char* fragmentShader =
"#version 460\n"
"in vec3 color;"
"out vec4 fragmentColor;"
"void main() {"
"fragmentColor = vec4(color, 1.0f);"
"}";

int _height = 460;
int _width = 640;

void WindowSizeCallback(GLFWwindow* window, int height, int width)
{
    _width = width;
    _height = height;
    glViewport(0, 0, _width, _height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(_width, _height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(gladLoadGL() == false)
    {
        return -1;
    }


    glClearColor(1, 0, 1, 0);

    std::string vertex(vertexShader);
    std::string fragment(fragmentShader);

    Renderer::ShaderProgram shaderProgram(vertex, fragment);
    if(shaderProgram.isCompiled() == false)
    {
        std::cerr << "cant create shader" << std::endl;
        return -1;
    }

    GLuint pointsVBO = 0;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


    GLuint colorsVBO = 0;
    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}