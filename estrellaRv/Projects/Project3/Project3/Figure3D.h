#ifndef FIGURE3D_H

#define FIGURE3D_H

#include <glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"

#define VERTEX_DATA     0
#define INDEX_DATA      1

//
// CLASE: Figure3D
//
// DESCRIPCIÓN: Clase abstracta que representa un objeto descrito mediante
//              VAO para su renderizado mediante shaders
// 
class Figure3D {
protected:
	GLushort* indexes;  // Array of indexes 
	GLfloat* vertices;  // Array of vertices

	GLuint numFaces;     // Number of faces
	GLuint numVertices;  // Number of vertices
	GLuint VBO[2];
	GLuint VAO;

public:
	~Figure3D();
	void InitBuffers();
	void Draw(ShaderProgram* program, glm::mat4 transform);
};

#endif