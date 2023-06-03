#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <log.h>
#include <model.h>
#include <resourcesManager.h>

#include <mat4.h>

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

bool SetupWindow(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSwapInterval(1); // Enable vsync
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    return true;
}

void SetupImGui(GLFWwindow* window)
{
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable viewports

    io.Fonts->AddFontDefault();

    // GL 3.3 + GLSL 330
    const char* const glslVersion = "#version 330";

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void StartImGuiFrame()
{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    SetupImGui(window);


    Log file;
    ResourcesManager resourceManager;
    Shader* myShader = resourceManager.Create<Shader>("Shader", "");

    myShader->SetUpShaders("./Assets/shaders/vertexShaderSource.shader", "./Assets/shaders/fragmentShaderSource.shader");

    //Model* model = resourceManager.Create<Model>("ModelCube", "./Assets/meshes/cube.obj");
    
    
    // -------------------------------- TEST -------------------------------------------

    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    // ----------------------- Texture --------------------

    Texture* texture1 = resourceManager.Create<Texture>("Container", "./Assets/textures/container.jpg");
    Texture* texture2 = resourceManager.Create<Texture>("Awesomeface", "./Assets/textures/awesomeface.png");
    
    myShader->use();
    myShader->setInt("texture1", 0);
    myShader->setInt("texture2", 1);

    // --------------------------- Main loop -------------------------

    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //reder
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //StartImGuiFrame();
        
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->texture);
        
        // create transformations
        Matrix4x4 trans;
        trans.IdentityMatrix();

        Vector3 vecTrans;
        vecTrans.value = { 0.5f, -0.5f, 0.0f };

        Vector3 vecRot;
        vecRot.value = { 0.0f, 0.0f, 1.0f };

        trans.translateMatrix(vecTrans);
        trans.rotate(vecRot.value[0], vecRot.value[1], vecRot.value[2],(float)glfwGetTime());
        
        myShader->use();
        myShader->setMat4("transform", trans);

        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
	return 0;
}