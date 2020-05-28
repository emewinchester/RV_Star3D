#ifndef SHADER_PROGRAM_H

#define SHADER_PROGRAM_H

#include <glew.h>
#include <glm/glm.hpp>

//
// CLASE: ShaderProgram
//
// DESCRIPCIÓN: Clase que desarrolla un programa GLSL
// 
class ShaderProgram {
private:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLboolean linked;
	char* logInfo;

	char ** GetVertexShaderFromResource();
	char ** GetFragmentShaderFromResource();

public:
	ShaderProgram();
	~ShaderProgram();
	GLboolean IsLinked();
	char* GetLog();
	GLvoid Use();
	GLvoid SetUniformF(char *name, GLfloat f);
	GLvoid SetUniformVec4(char *name, glm::vec4 m);
	GLvoid SetUniformVec3(char *name, glm::vec3 m);
	GLvoid SetUniformMatrix4(char *name, glm::mat4 m);
	GLvoid SetUniformI(char *name, GLint i);
};

#endif