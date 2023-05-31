#include <shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ------------- Function ---------------

string Shader::LoadShader(filesystem::path const& filename)
{
	ifstream fileShader;
	fileShader.open(filename);

	std::string str((std::istreambuf_iterator<char>(fileShader)), std::istreambuf_iterator<char>());
	return str.c_str();
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
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;

	}

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
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	return true;

}
bool Shader::Link()
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;

	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;

}


// ------------ Builder -----------------

Shader::Shader()
{
	

}