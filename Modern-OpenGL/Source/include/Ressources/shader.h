#pragma once
#include <resourcesManager.h>
#include <filesystem>


using namespace std;

class Shader : IResource
{

	int            success;
	char           infoLog[512];

	unsigned int   fragmentShader;
	unsigned int   vertexShader;

	//loader
	string LoadShader(filesystem::path const& filename);

	//read GLSL file
	bool SetVertexShader(filesystem::path const& filename);
	bool SetFragmentShader(filesystem::path const& filename);

public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragmentPath);

	// activate the shader
	// ------------------------------------------------------------------------
	void use() const;
	

	//ShaderProgram
	bool Link();

	//Buffer



};