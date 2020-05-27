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
	numFaces = puntas * 4; 
	//          vertices por punta + vertices por puntas internas + vertices por centro
	numVertices = (puntas * 4) + (puntas * 4) + (puntas * 4); 

	vertices = new GLfloat[numVertices * 3];
	indexes = new GLushort[numFaces * 3];


	int verticesIndex = 0;
	int incremento = (puntas * 2 + puntas * 2 + puntas * 2) * 3;

	int seguimiento = 0;

	/**         PUNTA CENTRAL          **/

	for (int i = 0; i < (puntas*2); i++) {

		// Puntas delanteras
		vertices[verticesIndex] = 0.0f;	// X
		vertices[verticesIndex + 1] = 0.0f;	// Y
		vertices[verticesIndex + 2] = ancho;	// Z


		// Puntas traseras
		vertices[verticesIndex + incremento] = 0.0f;	// X
		vertices[verticesIndex + 1 + incremento] = 0.0f;	// Y
		vertices[verticesIndex + 2 + incremento] = -ancho;	// Z

		seguimiento = verticesIndex;
		seguimiento = verticesIndex + 1;
		seguimiento = verticesIndex + 2;
		seguimiento = verticesIndex + incremento;
		seguimiento = verticesIndex + 1 + incremento;
		seguimiento = verticesIndex + 2 + incremento;

		verticesIndex += 3;
	}

	

	/**          RADIO EXTERIOR          **/

	// Empezamos por X = 0; Y = PI/2; Z = 0;
	float numPuntas = (float)puntas;
	float anguloInicio = 0.5 * PI;
	float anguloDeGiro = (2.0f / numPuntas) * PI;

	float anguloActual = anguloInicio;

	// Por cada punta
	for (int i = 0; i < puntas; i++) {

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			// Puntas delanteras
			vertices[verticesIndex] = radioExterior * cos(anguloActual);
			vertices[verticesIndex + 1] = radioExterior * sin(anguloActual);
			vertices[verticesIndex + 2] = 0.0f;

			// Puntas traseras
			vertices[verticesIndex + incremento] = radioExterior * cos(anguloActual);
			vertices[verticesIndex + 1 + incremento] = radioExterior * sin(anguloActual);
			vertices[verticesIndex + 2 + incremento] = 0.0f;


			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		anguloActual += anguloDeGiro;
	}



	/**         RADIO INTERIOR          **/

	// Creamos el primer vértice del radio interior fuera del bucle
	// Necesario para automatizar la creacion de los triangulos
	anguloInicio = 0.5 * PI - (2.0f / (numPuntas*2)) * PI;
	anguloActual = anguloInicio;

	// Punta delantera
	vertices[verticesIndex] = radioInterior * cos(anguloActual);
	vertices[verticesIndex + 1] = radioInterior * sin(anguloActual);
	vertices[verticesIndex + 2] = 0.0f;

	// Punta trasera
	vertices[verticesIndex + incremento] = radioInterior * cos(anguloActual);
	vertices[verticesIndex + 1 + incremento] = radioInterior * sin(anguloActual);
	vertices[verticesIndex + 2 + incremento] = 0.0f;

	verticesIndex += 3;

	// incrementamos el angulo en 2*PI/puntas
	anguloActual += anguloDeGiro;

	
	// Se crean para puntas-1
	for (int i = 0; i < (puntas-1); i++) {

		// Se generan 2 vertices
		for (int j = 0; j < 2; j++) {
			// Punta delantera
			vertices[verticesIndex] = radioInterior * cos(anguloActual);
			vertices[verticesIndex + 1] = radioInterior * sin(anguloActual);
			vertices[verticesIndex + 2] = 0.0f;

			//Punta trasera
			vertices[verticesIndex + incremento] = radioInterior * cos(anguloActual);
			vertices[verticesIndex + 1 + incremento] = radioInterior * sin(anguloActual);
			vertices[verticesIndex + 2 + incremento] = 0.0f;

			verticesIndex += 3;
		}

		// incrementamos el angulo en 2*PI/puntas
		anguloActual += anguloDeGiro;
	}

	// Creamos el último vértice interno manualmente, 
	// al igual que el primero

	vertices[verticesIndex] = radioInterior * cos(anguloActual);
	vertices[verticesIndex + 1] = radioInterior * sin(anguloActual);
	vertices[verticesIndex + 2] = 0.0f;

	vertices[verticesIndex + incremento] = radioInterior * cos(anguloActual);
	vertices[verticesIndex + 1 + incremento] = radioInterior * sin(anguloActual);
	vertices[verticesIndex + 2 + incremento] = 0.0f;

	verticesIndex += 3;





	/***         CREAMOS LOS TRIANGULOS         ***/

	int indexesIndex = 0;
	
	// parte delantera
	for (int i = 0; i < (puntas*2); i++) {

		if (i % 2 == 0) {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 4);
			indexes[indexesIndex + 2] = i + (puntas * 2);

			indexesIndex += 3;

		}
		else {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 2);
			indexes[indexesIndex + 2] = i + (puntas * 4);

			indexesIndex += 3;
		}
	}

	/*
	indexes[indexesIndex] = 30;
	indexes[indexesIndex + 1] = 50;
	indexes[indexesIndex + 2] = 40;

	indexesIndex += 3;

	indexes[indexesIndex] = 30;
	indexes[indexesIndex + 1] = 41;
	indexes[indexesIndex + 2] = 51;

	*/

	incremento = (puntas * 2 + puntas * 2 + puntas * 2);

	
	// parte trasera
	for (int i = 0; i < (puntas*2); i++) {
		if (i % 2 != 0) {
			indexes[indexesIndex] = i + incremento;
			indexes[indexesIndex + 1] = i + (puntas * 4) + incremento;
			indexes[indexesIndex + 2] = i + (puntas * 2) + incremento;

			indexesIndex += 3;

		}
		else {
			indexes[indexesIndex] = i + incremento;
			indexes[indexesIndex + 1] = i + (puntas * 2) + incremento;
			indexes[indexesIndex + 2] = i + (puntas * 4) + incremento;

			indexesIndex += 3;
		}
	}
	

	InitBuffers();
}