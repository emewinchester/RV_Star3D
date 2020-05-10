#include "stdafx.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model3D.h"
#include "Figure3D.h"
#include "ShaderProgram.h"
#include "Star3D.h"
#include "Prueba.h"

//
// FUNCIÓN: printError(char* msg)
//
// PROPÓSITO: Escribe un mensaje de error en el archivo "ErrorLog.txt"
//
void printError(char* msg)
{
	FILE* f;
	fopen_s(&f, "ErrorLog.txt", "w");
	fprintf(f, "%s", msg);
	fclose(f);
}


//
// FUNCIÓN: Initialize(GLsizei, GLsizei)
//
// PROPÓSITO: Initializa el modelo 3D
//
void Model3D::Initialize(GLsizei w, GLsizei h)
{
	// Crea el programa
	program = new ShaderProgram();
	if (program->IsLinked() == GL_TRUE) program->Use();
	else printError(program->GetLog());

	// Inicializa la posición de las figuras
	figure = 0; // muestra la figura 0 por defecto
	xAngle = 0.0f; // angulo de rotacion x
	yAngle = 0.0f; // angulo de rotacion y

	// Crea las figuras

	//fig8 = new Star3D(5, 5.0f, 25.0f, 1.0f); // Para la estrella
	fig8 = new Prueba(); // Para la estrella


	
	
	

	// Asigna el viewport y el clipping volume
	// Se genera la matriz de proyección en perspectiva 
	ChangeSize(w, h);

	// Opciones de dibujo
	glEnable(GL_DEPTH_TEST); // se activa el test de profundidad: lo que hay por delante puede eliminar lo que hay por detrás
	glEnable(GL_CULL_FACE); // Muestra las caras que se dibujan por detrás o no. No las dibuja
	glFrontFace(GL_CCW); // se indica que la cara frontal es la dibujada CCW (en contra de las agujas del reloj)
	glPolygonMode(GL_FRONT, GL_LINE); //GL_LINE: modo arista, GL_FILL: rellena la figura

	// Las caras vienen determinadas por el sentido en el que se dibujan los puntos de los triangulos
	// Lo normal: la cara frontal viene indicada por el sentido inverso a las agujas del reloj
}

//
// FUNCIÓN: Finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void Model3D::Finalize()
{

	// Para la estrella
	delete fig8;

	delete program;
}

//
// FUNCIÓN: ChangeSize(GLsizei, GLsizei)
//
// PROPÓSITO: Modifica la configuración del viewport al cambiar el tamaño de la ventana
//
void Model3D::ChangeSize(GLsizei w, GLsizei h)
{
	double fov = 15.0 * M_PI / 180.0;
	double sin_fov = sin(fov);
	double cos_fov = cos(fov);
	if (h == 0) h = 1;
	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
	GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
	GLfloat wWidth = wHeight * aspectRatio;

	glViewport(0, 0, w, h);

	// Se genera la matriz de proyección, proyección en perspectiva
	// frustrum: función que crea la perspectiva
	//                        left     richt    top      bottom   near  far
	// equivalencias                                              20 cm  400m
	projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
}


//
// FUNCIÓN: RenderScene()
//
// PROPÓSITO: Genera la imagen
//
void Model3D::RenderScene()
{
	// Limpia el framebuffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Matriz de transformación
	glm::mat4 location = glm::mat4(1.0f);
	location = glm::translate(location, glm::vec3(0.0f, 0.0f, -180.0f));

	// rotate necesita radianes, xAngle e yAngle estan en grados -> por eso se pasan a radianes
	location = glm::rotate(location, (GLfloat)(M_PI*yAngle / 180), glm::vec3(0.0f, 1.0f, 0.0f)); // eje y (0,1,0)
	location = glm::rotate(location, (GLfloat)(M_PI*xAngle / 180), glm::vec3(1.0f, 0.0f, 0.0f)); // eje x (1,0,0)


	// Vertex shader: transformacion que se aplica a los vertices. 
	//  matriz location: la que hace el giro
	glm::mat4 transform = projection*location;

	// NOTA: LOS VÉRTICES ROTAN CON LA FIGURA

	// En función del valor figure, se dibuja un objeto u otro
	switch (figure) {
	case 0: fig8->Draw(program, transform); break; // Para la estrella
	}

	
}

//
// FUNCIÓN: TimerAction()
//
// PROPÓSITO: Anima la escena
//
void Model3D::TimerAction()
{
}

//
// FUNCIÓN: KeyboardAction(int)
//
// PROPÓSITO: respuesta a acciones de teclado
//
void Model3D::KeyboardAction(int virtualKey)
{
	switch (virtualKey)
	{
	case VK_UP:
		xAngle += 5.0f;
		break;
	case VK_DOWN:
		xAngle -= 5.0f;
		break;
	case VK_LEFT:
		yAngle -= 5.0f;
		break;
	case VK_RIGHT:
		yAngle += 5.0f;
		break;
	case 'F':
		figure = (figure + 1) % 1;
		break;
	}
}

//
//  FUNCIÓN: MouseAction(int xPos, int yPos, WPARAM wParam)
//
//  PROPÓSITO: respuesta del modelo a un movimiento del ratón.
//
void Model3D::MouseAction(int button, int state, int x, int y)
{
}