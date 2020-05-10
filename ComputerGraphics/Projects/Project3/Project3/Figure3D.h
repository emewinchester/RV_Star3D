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
	GLushort* indexes;  // Array of indexes (guarda los índices de los triangulos: dibujar triangulos
						// con puntos 0-1-2, por ejemplo), la posicion en el vector indica el indice del triangulo

	GLfloat* vertices;  // Array of vertices (guarda las posiciones de los vertices)


	GLuint numFaces;     // Number of faces, numero de caras de la figuras (número de triángulos), 
						 //me indica el tamaño del array indixes
	GLuint numVertices;  // Number of vertices, numero de vertices que tenemos. Me indica el tamaño del array vertices
	GLuint VBO[2];		// necesito 1 buffer para almacenar la info de los vertices y otro para los indices
	GLuint VAO;			//necesito una estructura de datos que describa todo y esté asociada a lo que quiero hacer


public:
	~Figure3D();
	void InitBuffers();
	void Draw(ShaderProgram* program, glm::mat4 transform);
};

#endif

// Una figura 3D tiene vertices, 