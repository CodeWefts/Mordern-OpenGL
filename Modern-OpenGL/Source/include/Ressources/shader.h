#pragma once
#include <resourcesManager.h>
#include <filesystem>

using namespace std;

class Shader : IResource
{


public:

	Shader();

	//read GLSL file
	bool SetVertexShader(filesystem::path const& filename);
	bool SetFragmentShader(filesystem::path const& filename);

	//ShaderProgram
	bool Link();


};