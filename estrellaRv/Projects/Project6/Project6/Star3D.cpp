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
	// se consideran vértices distintos
	numFaces = puntas * 4; 
	//          vertices por punta + vertices por puntas internas + vertices por centro
	numVertices = (puntas * 4) + (puntas * 4) + (puntas * 4); 



	vertices = new GLfloat[numVertices * 3];
	indexes = new GLushort[numFaces * 3];
	normals = new GLfloat[numVertices * 3]; 
	textures = new GLfloat[numVertices * 2];

	

	int verticesIndex = 0;

	// incremento necesario para hacer la cara delantera y la trasera a la vez
	int incremento = (puntas * 2 + puntas * 2 + puntas * 2) * 3;



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

		// Se generan 2 vertices delanteros y 2 traseros
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

		// Se generan 2 vertices delanteros y 2 traseros
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





	/***         CREAMOS LOS TRIANGULOS        ***/


	int indexesIndex = 0;

	
	// parte delantera
	for (int i = 0; i < (puntas*2); i++) {

		if (i % 2 == 0) {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 4);
			indexes[indexesIndex + 2] = i + (puntas * 2);

		}
		else {
			indexes[indexesIndex] = i;
			indexes[indexesIndex + 1] = i + (puntas * 2);
			indexes[indexesIndex + 2] = i + (puntas * 4);
			
		}

		indexesIndex += 3;
	}



	incremento = (puntas * 2 + puntas * 2 + puntas * 2);

	
	// parte trasera
	for (int i = 0; i < (puntas*2); i++) {
		if (i % 2 != 0) {
			indexes[indexesIndex] = i + incremento;
			indexes[indexesIndex + 1] = i + (puntas * 4) + incremento;
			indexes[indexesIndex + 2] = i + (puntas * 2) + incremento;

		}
		else {
			indexes[indexesIndex] = i + incremento;
			indexes[indexesIndex + 1] = i + (puntas * 2) + incremento;
			indexes[indexesIndex + 2] = i + (puntas * 4) + incremento;
		}

		indexesIndex += 3;
	}


	

	/***         CREAMOS LAS NORMALES        ***/

	int normalsIndixes = 0;
	glm::vec3 central, exterior, interior, v1, v2, normal;
	int incRE = puntas * 2 * 3; // incremento para calcular el indice de la punta del radio exterior
	int incRI = (puntas * 2 + puntas * 2) * 3; // incremento para calcular el indice de la punta del radio interior
	int modulo = 0;

	// Parte delantera
	for (int i = 0; i < puntas * 4; i++) {

		if (i == puntas * 2) {
			normalsIndixes = (puntas * 2 + puntas * 2 + puntas * 2) * 3;
			modulo = 1;
		}

		central = glm::vec3(vertices[normalsIndixes], vertices[normalsIndixes + 1], vertices[normalsIndixes + 2]); 
		exterior = glm::vec3(vertices[normalsIndixes + incRE], vertices[normalsIndixes + incRE + 1], vertices[normalsIndixes + incRE + 2]);
		interior = glm::vec3(vertices[normalsIndixes + incRI], vertices[normalsIndixes + incRI + 1], vertices[normalsIndixes + incRI + 2]); 


		if (i % 2 == modulo) {
			v1 = interior - central;
			v2 = exterior - central;
		}
		else {
			v1 = exterior - central;
			v2 = interior - central;
		}


		// producto vectorial
		normal = glm::cross(v1, v2);


		// asignamos la normal a los vértices
		// Normal del vértice central
		normals[normalsIndixes] = normal[0];
		normals[normalsIndixes + 1] = normal[1];
		normals[normalsIndixes + 2] = normal[2];

		//normal del vertice exterior
		normals[normalsIndixes + incRE] = normal[0];
		normals[normalsIndixes + incRE + 1] = normal[1];
		normals[normalsIndixes + incRE + 2] = normal[2];

		//normal del vertice interior
		normals[normalsIndixes + incRI] = normal[0];
		normals[normalsIndixes + incRI + 1] = normal[1];
		normals[normalsIndixes + incRI + 2] = normal[2];

		normalsIndixes += 3;

	}



	/***         CALCULOS DE TEXTURAS        ***/

	int texturesIndexes = 0;

	incRE = puntas * 2 * 2; // incremento para calcular el indice de la punta del radio exterior
	incRI = (puntas * 2 + puntas * 2) * 2; // incremento para calcular el indice de la punta del radio interior

	int incTexturas = (puntas * 2 + puntas * 2 + puntas * 2) * 2;

	for (int i = 0; i < (puntas * 2 ); i++) {

		// cara delantera
		textures[texturesIndexes] = 0.0f; //x
		textures[texturesIndexes] = 0.0f; //y

		textures[texturesIndexes + incRE] = 0.0f; //x
		textures[texturesIndexes + incRE] = 1.0f; //y

		textures[texturesIndexes + incRI] = 1.0f; //x
		textures[texturesIndexes + incRI] = 1.0f; //y
		
		

		// cara trasera
		textures[texturesIndexes + incTexturas] = 0.0f; //x
		textures[texturesIndexes + incTexturas] = 0.0f; //y

		textures[texturesIndexes + incTexturas + incRE] = 0.0f; //x
		textures[texturesIndexes + incTexturas + incRE] = 1.0f; //y

		textures[texturesIndexes + incTexturas + incRI] = 1.0f; //x
		textures[texturesIndexes + incTexturas + incRI] = 1.0f; //y

		texturesIndexes += 2;
	}

	InitBuffers();
}