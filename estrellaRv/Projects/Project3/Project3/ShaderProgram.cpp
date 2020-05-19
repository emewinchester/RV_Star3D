#include "stdafx.h"
#include <glew.h>
#include "ShaderProgram.h"
#include "Project3.h"

ShaderProgram::ShaderProgram()
{
	GLint status;
	logInfo = NULL;

	// Crea y compila el vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, GetVertexShaderFromResource(), NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char *)malloc(sizeof(char)*logLength);
		GLsizei written;
		glGetShaderInfoLog(vertexShader, logLength, &written, logInfo);
		return;
	}

	// Crea y compila el fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, GetFragmentShaderFromResource(), NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char *)malloc(sizeof(char)*logLength);
		GLsizei written;
		glGetShaderInfoLog(fragmentShader, logLength, &written, logInfo);
		return;
	}

	//Crea y enlaza el programa
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		linked = GL_FALSE;
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		logInfo = (char *)malloc(sizeof(char)*logLength);
		GLsizei written;
		glGetProgramInfoLog(program, logLength, &written, logInfo);
		return;
	}

	linked = GL_TRUE;
}

char ** ShaderProgram::GetVertexShaderFromResource()
{
	HRSRC shaderHandle = FindResource(NULL, MAKEINTRESOURCE(IDR_HTML1), RT_HTML);
	HGLOBAL shaderGlobal = LoadResource(NULL, shaderHandle);
	LPCTSTR shaderPtr = static_cast<LPCTSTR>(LockResource(shaderGlobal));
	DWORD shaderSize = SizeofResource(NULL, shaderHandle);
	char* shaderCodeLine = (char*)malloc((shaderSize + 1)*sizeof(char));
	memcpy(shaderCodeLine, shaderPtr, shaderSize);
	shaderCodeLine[shaderSize] = '\0';
	char** shaderCode = (char**)malloc(sizeof(char*));
	shaderCode[0] = shaderCodeLine;
	UnlockResource(shaderGlobal);
	FreeResource(shaderGlobal);
	return shaderCode;
}

char ** ShaderProgram::GetFragmentShaderFromResource()
{
	HRSRC shaderHandle = FindResource(NULL, MAKEINTRESOURCE(IDR_HTML2), RT_HTML);
	HGLOBAL shaderGlobal = LoadResource(NULL, shaderHandle);
	LPCTSTR shaderPtr = static_cast<LPCTSTR>(LockResource(shaderGlobal));
	DWORD shaderSize = SizeofResource(NULL, shaderHandle);
	char* shaderCodeLine = (char*)malloc((shaderSize + 1)*sizeof(char));
	memcpy(shaderCodeLine, shaderPtr, shaderSize);
	shaderCodeLine[shaderSize] = '\0';
	char** shaderCode = (char**)malloc(sizeof(char*));
	shaderCode[0] = shaderCodeLine;
	UnlockResource(shaderGlobal);
	FreeResource(shaderGlobal);
	return shaderCode;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

GLboolean ShaderProgram::IsLinked()
{
	return linked;
}

char* ShaderProgram::GetLog()
{
	return logInfo;
}

GLvoid ShaderProgram::Use()
{
	glUseProgram(program);
}


void ShaderProgram::SetUniformF(char * name, GLfloat f)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniform1f(location, f);
}

GLvoid ShaderProgram::SetUniformMatrix4(char *name, glm::mat4 m)
{
	GLuint location = glGetUniformLocation(program, name);
	if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}
