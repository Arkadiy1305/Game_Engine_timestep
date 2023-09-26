#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	int success{};
	char infoLog[512];
	UINT32 vertex, fragment;
	vertex = compileShader(GL_VERTEX_SHADER, vertexPath);	
	fragment = compileShader(GL_FRAGMENT_SHADER, fragmentPath);
	if (vertex && fragment)
	{
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::activate()
{
	glUseProgram(m_ID);
}

void ShaderProgram::setBool(const std::string& name, bool value)
{
}

void ShaderProgram::setInt(const std::string& name, int value)
{
}

void ShaderProgram::setFloat(const std::string& name, float value)
{
}

void ShaderProgram::setMat4(const char* name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

UINT32 ShaderProgram::compileShader(const GLenum typeShader, const char* pathToShader)
{
	std::string code;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(pathToShader);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		code = shaderStream.str();
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE " << pathToShader << " NOT SUCCESSFULLY READ"  << '\n';
	}
	const char* shaderCode = code.c_str();
	UINT32 shaderName;
	int success{};
	char infoLog[512];

	shaderName = glCreateShader(typeShader);
	glShaderSource(shaderName, 1, &shaderCode, nullptr);
	glCompileShader(shaderName);
	glGetShaderiv(shaderName, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderName, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILING_ERROR\n" << infoLog << '\n';
		return success;
	}
	return shaderName;
}

