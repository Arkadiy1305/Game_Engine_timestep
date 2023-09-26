#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexPath, const char* fragmentPath);
	~ShaderProgram();
	ShaderProgram() = delete;
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram operator = (const ShaderProgram&) = delete;
	ShaderProgram(const ShaderProgram&&) = delete;
	void activate();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
    void setMat4(const char* name, const glm::mat4& value);
	UINT32 get_id() const { return m_ID; };
	
	
private:
	UINT32 m_ID{ 0 };
	UINT32 compileShader(const GLenum typeShader, const char* pathToShader);
};