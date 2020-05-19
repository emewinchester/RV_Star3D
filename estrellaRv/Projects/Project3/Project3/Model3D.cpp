#include "stdafx.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model3D.h"
#include "Figure3D.h"
#include "Star3D.h"
#include "ShaderProgram.h"

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
	xAngle = 0.0f;
	yAngle = 0.0f;

	// Crea las figuras
	fig0 = new Star3D(6, 8.0f, 25.0f, 5.0f); 
	//GLint puntas, GLfloat radioInterior, GLfloat radioExterior, GLfloat ancho


	// Asigna el viewport y el clipping volume
	ChangeSize(w, h);

	// Opciones de dibujo
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
}

//
// FUNCIÓN: Finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void Model3D::Finalize()
{
	delete fig0;
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
	location = glm::rotate(location, (GLfloat)(M_PI*yAngle / 180), glm::vec3(0.0f, 1.0f, 0.0f));
	location = glm::rotate(location, (GLfloat)(M_PI*xAngle / 180), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 transform = projection*location;

	
	fig0->Draw(program, transform); 

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