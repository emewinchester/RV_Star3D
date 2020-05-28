#include "stdafx.h"
#include <glew.h>
#include <math.h>
#include "Figure3D.h"
#include "Piramid3D.h"

Piramid3D::Piramid3D(GLfloat s)
{
	double sqrt_5 = sqrt(5.0);
	double normal1 = (GLfloat)(1.0 / sqrt_5);
	double normal2 = (GLfloat)(2.0 / sqrt_5);

	numFaces = 6;     // Number of faces
	numVertices = 16;  // Number of vertices

	GLfloat p_vertices[16][3] = {
		{ 0.0f, 0.0f, s }, // E // Positive X
		{ s, -s, -s },     // B  
		{ s, s, -s },      // A

		{ 0.0f, 0.0f, s }, // E // Positive Y
		{ s, s, -s },      // A
		{ -s, s, -s },     // D

		{ 0.0f, 0.0f, s }, // E // Negative X
		{ -s, s, -s },     // D
		{ -s, -s, -s },    // C

		{ 0.0f, 0.0f, s }, // E // Negative Y
		{ -s, -s, -s },    // C
		{ s, -s, -s },     // B  

		{ s, s, -s },      // A // Negative Z
		{ s, -s, -s },     // B  
		{ -s, -s, -s },    // C
		{ -s, s, -s },     // D
	};

	GLfloat p_normals[16][3] = {
		{ normal2, 0.0f, normal1 },   // Positive X 
		{ normal2, 0.0f, normal1 },
		{ normal2, 0.0f, normal1 },
		{ 0.0f, normal2, normal1 },   // Positive Y 
		{ 0.0f, normal2, normal1 },
		{ 0.0f, normal2, normal1 },
		{ -normal2, 0.0f, normal1 },  // Negative X
		{ -normal2, 0.0f, normal1 },
		{ -normal2, 0.0f, normal1 },
		{ 0.0f, -normal2, normal1 },  // Negative Y
		{ 0.0f, -normal2, normal1 },
		{ 0.0f, -normal2, normal1 },
		{ 0.0f, 0.0f, -1.0f },       // Negative Z 
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f }
	};

	GLfloat p_textures[16][2] = { // Array of texture coordinates
		{ 0.5f, 1.0f },  // Triangle
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.5f, 1.0f },  // Triangle
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.5f, 1.0f },  // Triangle
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.5f, 1.0f },  // Triangle
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },  // Base
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f }
	};

	GLushort p_indexes[6][3] = {  // Array of indexes
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 },
		{ 9, 10, 11 },
		{ 12, 13, 14 },
		{ 12, 14, 15 }
	};

	normals = new GLfloat[numVertices * 3];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 3; j++) normals[3 * i + j] = p_normals[i][j];
	vertices = new GLfloat[numVertices * 3];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 3; j++) vertices[3 * i + j] = p_vertices[i][j];
	textures = new GLfloat[numVertices * 2];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 2; j++) textures[2 * i + j] = p_textures[i][j];
	indexes = new GLushort[numFaces * 3];
	for (int i = 0; i < numFaces; i++) for (int j = 0; j < 3; j++) indexes[3 * i + j] = p_indexes[i][j];

	InitBuffers();
}
