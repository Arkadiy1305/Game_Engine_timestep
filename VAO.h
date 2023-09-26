#pragma once
#include <glad/glad.h>

class VAO
{
public:
	VAO();
	~VAO();
	void bind();
	unsigned int get_ID() const { return m_ID; }
	void create_vbo(GLsizeiptr size, GLfloat* vertices);

private:
	unsigned int m_ID{};
	unsigned int m_VBO{};
};

VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);	
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_ID);
}

inline void VAO::bind()
{
	glBindVertexArray(m_ID);
}

inline void VAO::create_vbo(GLsizeiptr size, GLfloat* vertices)
{
	glGenBuffers(1, &m_VBO);
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);
}
