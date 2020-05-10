#include "stdafx.h"
#include <glew.h>
#include <math.h>
#include "Figure3D.h"
#include "Star3D.h"
#include <iostream>

#define PI 3.1416

using namespace std;

Star3D::Star3D(GLfloat puntas, GLfloat radioInterior, GLfloat radioExterior, GLfloat ancho) {

	

	// Nota: por cada triángulo que converge en un punto, 
	// se consideran vértices distinto
	numFaces = puntas * 2; 
	//            vertices por punta + vertices por puntas internas + vertices por centro
	numVertices = (puntas * 2) + (2 * puntas) + (puntas * 2); 
	//numVertices = (puntas * 2 * 2) + (2 * puntas * 2) + (puntas * 2 * 2);


	vertices = new GLfloat[numVertices * 3];
	indexes = new GLushort[numFaces * 3];


	int verticesIndex = 0;

	/**         CARA FRONTAL , PUNTA CENTRAL          **/

	//CARA FRONTAL , PUNTA CENTRAL
	for (int i = 0; i < 10; i++) {
		vertices[verticesIndex] = 0.0f;	// X
		vertices[verticesIndex + 1] = 0.0f;	// Y
		vertices[verticesIndex + 2] = 5.0f;	// Z

		verticesIndex += 3;
	}

	

	/**         CARA FRONTAL , RADIO EXTERIOR          **/

	float x; // coordenada x
	float y; // coordenada y
	float angulo = 0.5 * PI;

	// Por cada punta
	for (int i = 0; i < puntas; i++) {

		x = radioExterior * cos(angulo);
		y = radioExterior * sin(angulo);

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = (GLfloat)x;
			vertices[verticesIndex + 1] = (GLfloat)y;
			vertices[verticesIndex + 2] = 0.0f;

			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		angulo += (2.0f / puntas) * PI;
	}



	/**         CARA FRONTAL , RADIO INTERIOR          **/

	// Creamos el primer vértice del radio interior fuera del bucle
	// Necesario para automatizar la creacion de los triangulos
	angulo = (1 / 2) * PI - (2 / (puntas*2)) * PI;

	x = radioInterior * cos(angulo);
	y = radioInterior * sin(angulo);
	
	vertices[verticesIndex] = (GLfloat)x;
	vertices[verticesIndex + 1] = (GLfloat)y;
	vertices[verticesIndex + 2] = 0.0f;

	verticesIndex += 3;

	// incrementamos el angulo en 2*PI/puntas
	angulo += (2 / puntas) * PI;

	
	// Se crean para puntas-1
	for (int i = 0; i < puntas-1; i++) {

		x = radioInterior * cos(angulo);
		y = radioInterior * sin(angulo);

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = (GLfloat)x;
			vertices[verticesIndex + 1] = (GLfloat)y;
			vertices[verticesIndex + 2] = 0.0f;

			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		angulo += (2.0f / puntas) * PI;
	}

	// Creamos el último vértice interno manualmente, 
	// al igual que el primero
	x = radioInterior * cos(angulo);
	y = radioInterior * sin(angulo);

	vertices[verticesIndex] = (GLfloat)x;
	vertices[verticesIndex + 1] = (GLfloat)y;
	vertices[verticesIndex + 2] = 0.0f;

	verticesIndex += 3;



	/***         CREAMOS LOS TRIANGULOS         ***/

	int indexesIndex = 0;
	/*
	indexes[indexesIndex] = 0;
	indexes[indexesIndex + 1] = 20;
	indexes[indexesIndex + 2] = 10;
	indexesIndex += 3;

	indexes[indexesIndex] = 1;
	indexes[indexesIndex + 1] = 11;
	indexes[indexesIndex + 2] = 21;
	indexesIndex += 3;

	indexes[indexesIndex] = 2;
	indexes[indexesIndex + 1] = 22;
	indexes[indexesIndex + 2] = 12;
	indexesIndex += 3;

	indexes[indexesIndex] = 3;
	indexes[indexesIndex + 1] = 13;
	indexes[indexesIndex + 2] = 23;
	indexesIndex += 3;

	indexes[indexesIndex] = 4;
	indexes[indexesIndex + 1] = 24;
	indexes[indexesIndex + 2] = 14;
	indexesIndex += 3;

	indexes[indexesIndex] = 5;
	indexes[indexesIndex + 1] = 15;
	indexes[indexesIndex + 2] = 25;
	indexesIndex += 3;

	indexes[indexesIndex] = 6;
	indexes[indexesIndex + 1] = 26;
	indexes[indexesIndex + 2] = 16;
	indexesIndex += 3;

	indexes[indexesIndex] = 7;
	indexes[indexesIndex + 1] = 17;
	indexes[indexesIndex + 2] = 27;
	indexesIndex += 3;

	indexes[indexesIndex] = 8;
	indexes[indexesIndex + 1] = 28;
	indexes[indexesIndex + 2] = 18;
	indexesIndex += 3;

	indexes[indexesIndex] = 9;
	indexes[indexesIndex + 1] = 19;
	indexes[indexesIndex + 2] = 29;
	indexesIndex += 3;*/

	/*
	for (int i = 0; i < (puntas * 2); i++) {
		indexes[indexesIndex] = i;
		indexes[indexesIndex + 1] = i + (puntas * 4);
		indexes[indexesIndex + 2] = i +  (puntas * 2);

		indexesIndex += 3;
	}*/

	for (int i = 0; i < (1); i++) {

		if (i % 2 == 0) {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 4);
			indexes[indexesIndex + 2] = i + (puntas * 2);

			
		}
		else {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 4);
			indexes[indexesIndex + 2] = i + (puntas * 2);
		}
		
		indexesIndex += 3;
	}

	InitBuffers();
}