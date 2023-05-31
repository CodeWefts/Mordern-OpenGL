#include <shader.h>


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
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		return false;

	}

	cout << "ERROR::SHADER::VERTEX::COMPILATION_SUCCED\n" << endl;

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
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;

		return false;
	}

	cout << "ERROR::SHADER::FRAGMENT::COMPILATION_SUCCED\n" <<endl;
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
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		return false;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;

}

// ------------ Builder -----------------

Shader::Shader(const char* vertexPath, const char* fragmentPath)
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
