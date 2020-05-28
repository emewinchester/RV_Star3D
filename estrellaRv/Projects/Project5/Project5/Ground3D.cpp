#include "stdafx.h"
#include <glew.h>
#include "Figure3D.h"
#include "Ground3D.h"


Ground3D::Ground3D(GLfloat l1, GLfloat l2)
{
	numFaces = 2;     // Number of faces
	numVertices = 4;  // Number of vertices

	GLfloat p_vertices[4][3] = {
		{ l1, 0.0f, l2 },
		{ l1, 0.0f, -l2 },
		{ -l1, 0.0f, -l2 },
		{ -l1, 0.0f, l2 }
	};

	GLfloat p_normals[4][3] = {
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f }
	};

	GLushort p_indexes[2][3] = {
		{ 0, 1, 2 },
		{ 0, 2, 3 }
	};

	vertices = new GLfloat[numVertices * 3];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 3; j++) vertices[3 * i + j] = p_vertices[i][j];
	normals = new GLfloat[numVertices * 3];
	for (int i = 0; i < numVertices; i++) for (int j = 0; j < 3; j++) normals[3 * i + j] = p_normals[i][j];
	indexes = new GLushort[numFaces * 3];
	for (int i = 0; i < numFaces; i++) for (int j = 0; j < 3; j++) indexes[3 * i + j] = p_indexes[i][j];

	InitBuffers();
}
