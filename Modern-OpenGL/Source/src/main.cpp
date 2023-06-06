#include <app.h>
#include <log.h>

int main(int argc, char** argv)
{
    App* app = new App();


    Log file;
    file.OpenFile("./Assets/log/log.txt");

    // ----------------------- Setup Glfw window ---------------------

    if (!app->SetupGlfw())
        return -1;

    GLFWwindow* window = app->CreateWindow();

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!app->SetupWindow(window))
        return -1;

    app->SetupImGui(window);
    

    app->Init();

    // --------------------------- Main loop -------------------------
    while (!glfwWindowShouldClose(window))
    {
        app->deltaTime = ImGui::GetIO().DeltaTime;

        // input
        // -----
        app->processInput(window);

        app->Update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    app->Delete();
    

    glfwTerminate();
	return 0;
}