#pragma once
#include <iresource.h>
#include <filesystem>
#include <vec2.h>
#include <vec3.h>
#include <vec4.h>
#include <mat4.h>

using namespace std;

class Shader : public IResource
{
private:
	int            success;
	char           infoLog[512];

	unsigned int   vertexShader;
	unsigned int   fragmentShader;

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
	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const Vector2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const Vector3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const Vector4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat4(const std::string& name, Matrix4x4 mat) const;


};