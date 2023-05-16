#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





bool SetupGlfw()
{
    glfwSetErrorCallback([](int error, const char* description)
        {
            std::cerr << "GLFW error " << error << ": " << description << std::endl;
        }
    );

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CENTER_CURSOR, true);
    glfwWindowHint(GLFW_MAXIMIZED, true);

    return true;
}

GLFWwindow* CreateWindow()
{
    return glfwCreateWindow(800, 600, "Modern-OpenGL", nullptr, nullptr);
}

bool SetupWindow(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSwapInterval(1); // Enable vsync
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    return true;
}



int main(int argc, char** argv)
{
    // ----------------------- Setup Glfw window ---------------------

    if (!SetupGlfw())
        return -1;

	GLFWwindow* window = CreateWindow();

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!SetupWindow(window))
        return -1;


    // --------------------------- Main loop -------------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	return 0;
}