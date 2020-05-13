#include "stdafx.h"
#include <glew.h>
#include <math.h>
#include "Figure3D.h"
#include "Star3D.h"
#include <iostream>

#define PI 3.1416

using namespace std;

Star3D::Star3D(GLint puntas, GLfloat radioInterior, GLfloat radioExterior, GLfloat ancho) {

	

	// Nota: por cada triángulo que converge en un punto, 
	// se consideran vértices distinto

	

	// Por ahora consideramos solo que vamos a hacer una cara
	numFaces = puntas * 2; 
	//            vertices por punta + vertices por puntas internas + vertices por centro
	numVertices = (puntas * 2) + (2 * puntas) + (puntas * 2); 
	//numVertices = (puntas * 2 * 2) + (2 * puntas * 2) + (puntas * 2 * 2);


	vertices = new GLfloat[numVertices * 3];
	indexes = new GLushort[numFaces * 3];


	int verticesIndex = 0;

	/**         CARA FRONTAL , PUNTA CENTRAL          **/

	//CARA FRONTAL , PUNTA CENTRAL
	for (int i = 0; i < (puntas*2); i++) {

		vertices[verticesIndex] = 0.0f;	// X
		vertices[verticesIndex + 1] = 0.0f;	// Y
		vertices[verticesIndex + 2] = ancho;	// Z

		verticesIndex += 3;
	}

	

	/**         CARA FRONTAL , RADIO EXTERIOR          **/

	float numPuntas = (float)puntas;

	// empezamos en EJEX = 0; EJE Y = PI/2; EJE Z = 0;
	float angulo = 0.5 * PI; 
	float anguloDeGiro = (2.0f / numPuntas) * PI;
	

	// Por cada punta
	for (int i = 0; i < puntas; i++) {

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = radioExterior * cos(angulo); // x
			vertices[verticesIndex + 1] = radioExterior * sin(angulo); // y
			vertices[verticesIndex + 2] = 0.0f; // z

			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		angulo += anguloDeGiro;
	}



	/**         CARA FRONTAL , RADIO INTERIOR          **/

	// Creamos el primer vértice del radio interior fuera del bucle
	// Necesario para automatizar la creacion de los triangulos
	angulo = 0.5 * PI - (2.0f / (numPuntas*2)) * PI;

	vertices[verticesIndex] = radioInterior * cos(angulo); // x
	vertices[verticesIndex + 1] = radioInterior * sin(angulo); // y
	vertices[verticesIndex + 2] = 0.0f; // z

	verticesIndex += 3;

	// incrementamos el angulo en 2*PI/puntas
	angulo += anguloDeGiro;

	
	// Se crean para puntas-1
	for (int i = 0; i < puntas-1; i++) {

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = radioInterior * cos(angulo); // x
			vertices[verticesIndex + 1] = radioInterior * sin(angulo); // y
			vertices[verticesIndex + 2] = 0.0f; // z

			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		angulo += anguloDeGiro;
	}

	// Creamos el último vértice interno manualmente, 
	// al igual que el primero
	vertices[verticesIndex] = radioInterior * cos(angulo); // x
	vertices[verticesIndex + 1] = radioInterior * sin(angulo); // y
	vertices[verticesIndex + 2] = 0.0f; // z

	verticesIndex += 3;



	/***         CREAMOS LOS TRIANGULOS         ***/

	int indexesIndex = 0;

	for (int i = 0; i < (puntas*2); i++) {

		if (i % 2 == 0) {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (5 * 4);
			indexes[indexesIndex + 2] = i + (5 * 2);

			indexesIndex += 3;

		}
		else {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (5 * 2);
			indexes[indexesIndex + 2] = i + (5 * 4);

			indexesIndex += 3;
		}


	}

	InitBuffers();
}