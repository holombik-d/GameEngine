#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}