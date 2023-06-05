#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <log.h>
#include <model.h>
#include <resourcesManager.h>
#include <camera.h>

#include <mat4.h>

#define PI 3.14159265359f
#define TO_RAD(var) ((var * PI) / 180.f)

// settings
const int WIDTH = 1200;
const int HEIGHT = 800;

// camera
Camera camera(Vector3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


Vector3 lightPos(1.2f, 1.0f, 2.0f);

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
    //glfwWindowHint(GLFW_MAXIMIZED, true);

    return true;
}

GLFWwindow* CreateWindow()
{
    return glfwCreateWindow(WIDTH, HEIGHT, "Modern-OpenGL", nullptr, nullptr);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

bool SetupWindow(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
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
    Shader* lightingShader = resourceManager.Create<Shader>("LightingShader", "");
    Shader* lightCubeShader = resourceManager.Create<Shader>("LightCubeShader", "");

    glEnable(GL_DEPTH_TEST);

    lightingShader->SetUpShaders("./Assets/shaders/lightVertexSource.shader", "./Assets/shaders/lightFragmentSource.shader");
    lightCubeShader->SetUpShaders("./Assets/shaders/lightCubeVertexSource.shader", "./Assets/shaders/lightCubeFragmentSource.shader");
    
    // -------------------------------- TEST -------------------------------------------

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // positions all containers
    Vector3 cubePositions[] = {
        Vector3(0.0f,  0.0f,  0.0f),
        Vector3(2.0f,  5.0f, -15.0f),
        Vector3(-1.5f, -2.2f, -2.5f),
        Vector3(-3.8f, -2.0f, -12.3f),
        Vector3(2.4f, -0.4f, -3.5f),
        Vector3(-1.7f,  3.0f, -7.5f),
        Vector3(1.3f, -2.0f, -2.5f),
        Vector3(1.5f,  2.0f, -2.5f),
        Vector3(1.5f,  0.2f, -1.5f),
        Vector3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    Vector3 pointLightPositions[] = {
        Vector3(0.7f,  0.2f,  2.0f),
        Vector3(2.3f, -3.3f, -4.0f),
        Vector3(-4.0f,  2.0f, -12.0f),
        Vector3(0.0f,  0.0f, -3.0f)
    };

    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO); // GENERAL

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ---------- TEXTURE ----------------
    Texture* texture1 = resourceManager.Create<Texture>("Container2", "./Assets/textures/container2.png");
    Texture* texture2 = resourceManager.Create<Texture>("Container2_Specular","./Assets/textures/container2_specular.png");

    lightingShader->use();
    lightingShader->setInt("material.diffuse", 0);
    lightingShader->setInt("material.specular", 1);

    // --------------------------- Main loop -------------------------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader->use();
        lightingShader->setVec3("viewPos", camera.position);
        lightingShader->setFloat("material.shininess", 32.0f);

        // directional light
        lightingShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[0].constant", 1.0f);
        lightingShader->setFloat("pointLights[0].linear", 0.09f);
        lightingShader->setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[1].constant", 1.0f);
        lightingShader->setFloat("pointLights[1].linear", 0.09f);
        lightingShader->setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[2].constant", 1.0f);
        lightingShader->setFloat("pointLights[2].linear", 0.09f);
        lightingShader->setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        lightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("pointLights[3].constant", 1.0f);
        lightingShader->setFloat("pointLights[3].linear", 0.09f);
        lightingShader->setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        lightingShader->setVec3("spotLight.position", camera.position);
        lightingShader->setVec3("spotLight.direction", camera.front);
        lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader->setFloat("spotLight.constant", 1.0f);
        lightingShader->setFloat("spotLight.linear", 0.09f);
        lightingShader->setFloat("spotLight.quadratic", 0.032f);
        lightingShader->setFloat("spotLight.cutOff", cos(TO_RAD(12.5f)));
        lightingShader->setFloat("spotLight.outerCutOff", cos(TO_RAD(15.0f)));


        // ---------------------------  create transformations  -------------------------------------------------------------
        
        /*
        Vector3 diffuse(0.5f, 0.5f, 0.5f);
        Vector3 ambient(0.2f, 0.2f, 0.2f);

        Vector3 lightColor(1.0f,1.0f,1.0f);

        Vector3 diffuseColor = lightColor * diffuse;
        Vector3 ambientColor = diffuseColor * ambient;
        */

        Vector3 rotation0(1.0f, 0.0f, 0.0f);
        Vector3 rotation1(0.0f, 1.0f, 0.0f);
        Vector3 rotation2(0.0f, 0.0f, 1.0f);
        Vector3 scaling(0.2f, 0.2f, 0.2f);

        // ---------------------- CUBE --------------------
        Matrix4x4 projection;
        projection.Perspective(TO_RAD(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        lightingShader->setMat4("projection", projection);

        Matrix4x4 view = camera.GetViewMatrix();
        lightingShader->setMat4("view", view);
        
        Matrix4x4 model;
        model.IdentityMatrix();
        lightingShader->setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->id);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->id);

        // render containers
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            Matrix4x4 model; model.IdentityMatrix();
            
            model.translateMatrix(cubePositions[i]);
            float angle = 20.0f * i;
            model.rotate(TO_RAD(angle), rotation0);
            model.rotate(TO_RAD(angle), rotation1);
            model.rotate(TO_RAD(angle), rotation2);
            lightingShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ----------------------- LIGHT CUBE ----------------
        
        lightCubeShader->use();
        lightCubeShader->setMat4("projection", projection);
        lightCubeShader->setMat4("view", view);

        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model.IdentityMatrix();
            model.translateMatrix(pointLightPositions[i]);
            model.scale(scaling); // Make it a smaller cube
            lightCubeShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
	return 0;
}