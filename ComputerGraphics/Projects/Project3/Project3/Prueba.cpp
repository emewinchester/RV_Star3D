#include "stdafx.h"
#include <glew.h>
#include <math.h>
#include "Figure3D.h"
#include "Prueba.h"
#include <iostream>

#define PI 3.1416

Prueba::Prueba() {

	numFaces = 5 * 2;
	//            vertices por punta + vertices por puntas internas + vertices por centro
	numVertices = 30;
	
	// Dibujamos primero el centro

	vertices = new GLfloat[numVertices * 3];
	indexes = new GLushort[numFaces * 3];

	int verticesIndex = 0;

	//CARA FRONTAL , PUNTA CENTRAL
	for (int i = 0; i < 10; i++) {
		vertices[verticesIndex] = 0.0f;	// X
		vertices[verticesIndex + 1] = 0.0f;	// Y
		vertices[verticesIndex + 2] = 5.0f;	// Z

		verticesIndex += 3;
	}
	



	// CARA FRONTAL, RADIO EXTERIOR

	float angulo = 0.5 * PI;
	float radioE = 25.0f;

	float x;
	float y;

	// por cada punta, se crean 2 vertices
	for (int i = 0; i < 5; i++) {

		x = radioE * cos(angulo);
		y = radioE * sin(angulo);

		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = x;	// X
			vertices[verticesIndex + 1] = y;	// Y
			vertices[verticesIndex + 2] = 0.0f;	// Z

			verticesIndex += 3;
		}
		
		angulo += (0.4 * PI);
	}


	// CARA FRONTAL, RADIO INTERIOR
	
	angulo = (0.5 * PI) - (0.2 * PI);
	float radioI = 8.0f;

	// Creo el primer vertice fuera
	vertices[verticesIndex] = radioI * cos(angulo);	// X
	vertices[verticesIndex + 1] = radioI * sin(angulo);	// Y
	vertices[verticesIndex + 2] = 0.0f;	// Z

	verticesIndex += 3;
	angulo += (0.4 * PI);


	for (int i = 0; i < 4; i++) {
		x = radioI * cos(angulo);
		y = radioI * sin(angulo);

		for (int j = 0; j < 2; j++) {
			vertices[verticesIndex] = x;	// X
			vertices[verticesIndex + 1] = y;	// Y
			vertices[verticesIndex + 2] = 0.0f;	// Z

			verticesIndex += 3;
		}
	
		angulo += (0.4 * PI);
	}

	// Creo el último vertice fuera del buce¡le
	vertices[verticesIndex] = radioI * cos(angulo);	// X
	vertices[verticesIndex + 1] = radioI * sin(angulo);	// Y
	vertices[verticesIndex + 2] = 0.0f;	// Z

	int indexesIndex = 0;
	
	
	for (int i = 0; i < (10); i++) {

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
	indexesIndex += 3;

	*/
	
	InitBuffers();


}