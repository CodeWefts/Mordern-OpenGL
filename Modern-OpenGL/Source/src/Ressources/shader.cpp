#include <shader.h>
#include <log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ------------- Function ---------------

string Shader::LoadShader(filesystem::path const& filename)
{
	ifstream fileShader;
	fileShader.open(filename);

	if (fileShader)
	{
		string str((istreambuf_iterator<char>(fileShader)), istreambuf_iterator<char>());
		return str.c_str();
	}
	return "";
}


bool Shader::SetVertexShader(filesystem::path const& filename)
{
	string vertexShaderSTR = LoadShader(filename);
	const char* vertexShaderCHAR = vertexShaderSTR.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCHAR, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		DEBUG_LOG( "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" , infoLog );
		return false;

	}

	DEBUG_LOG( "SHADER::VERTEX::COMPILATION_SUCCED\n");

	return true;
}

bool  Shader::SetFragmentShader(filesystem::path const& filename)
{
	string fragmentShaderSTR = LoadShader(filename);
	const char* fragmentShaderCHAR = fragmentShaderSTR.c_str();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCHAR, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		DEBUG_LOG( "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog );

		return false;
	}

	DEBUG_LOG( "SHADER::FRAGMENT::COMPILATION_SUCCED\n" );
	return true;
}


void Shader::use() const
{
	glUseProgram(id);
}

bool Shader::Link()
{
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	// check for linking errors
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(id, 1024, NULL, infoLog);
		DEBUG_LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s \n", infoLog);
		return false;
	}

	DEBUG_LOG("LINK::FRAGMENT::COMPILATION_SUCCED\n");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;

}

void Shader::SetUpShaders(const char* vertexPath, const char* fragmentPath)
{
	// retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;

	ifstream vShaderFile;
	ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// vertex shader
	SetVertexShader(vertexPath);

	// fragment Shader
	SetFragmentShader(fragmentPath);

	// shader Program
	Link();

}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const Vector2& value) const
{
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value.value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const Vector3& value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value.x);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const Vector4& value) const
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value.x);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, Matrix4x4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_TRUE, &mat.Array()[0]);
}


// ------------ Builder -----------------

Shader::Shader()
{

}


void Shader::LoadResource(string const& filename)
{

}
void Shader::UnloadResource()
{

}
