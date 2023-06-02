#pragma once
#include <iresource.h>
#include <filesystem>


using namespace std;

class Shader : public IResource
{
private:
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

	Shader();

	void LoadResource(string const& filename);
	void UnloadResource();

	// activate the shader
	// ------------------------------------------------------------------------
	void use() const;
	

	//ShaderProgram
	bool Link();

	//SetUp
	void SetUpShaders(const char* vertexPath, const char* fragmentPath);



};