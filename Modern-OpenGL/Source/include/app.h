#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"


#include <shader.h>
#include <texture.h>
#include <light.h>
#include <scene.h>
#include <resourcesManager.h>

class App
{

	ResourcesManager resourceManager;
	Light light;
	Scene scene;
	Texture texture;


	unsigned int VBO,lightCubeVAO, cubeVAO;

public:
	float deltaTime = 0.0f;	// time between current frame and last frame



	bool SetupGlfw();
	GLFWwindow* CreateWindow();
	bool SetupWindow(GLFWwindow* window);
	void SetupImGui(GLFWwindow* window);
	void StartImGuiFrame();
	void processInput(GLFWwindow* window);



	int Init();
	void Update();
	void Delete();

	App();
};