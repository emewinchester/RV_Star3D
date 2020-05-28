#include "stdafx.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model3D.h"

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
// FUNCIÓN: Model3D::Initialize(GLsizei, GLsizei)
//
// PROPÓSITO: Initializa el modelo 3D
//
void Model3D::Initialize(GLsizei w, GLsizei h)
{
	// Crea el programa
	program = new ShaderProgram();
	if (program->IsLinked() == GL_TRUE) program->Use();
	else printError(program->GetLog());


	// Crea la cámara y la matriz View
	camera = new Camera3D();
	camera->SetPosition(0.0f, 5.0f, 30.0f);

	// Inicializa la posición de las figuras
	scene = new Scene3D();

	// Asigna el viewport y el clipping volume
	ChangeSize(w, h);

	// Opciones de dibujo
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDepthFunc(GL_LEQUAL);
}


//
// FUNCIÓN: Model3D::Finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void Model3D::Finalize()
{
	delete camera;
	delete scene;
	delete program;
}

//
// FUNCIÓN: Model3D::ChangeSize(GLsizei, GLsizei)
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
// FUNCIÓN: Model3D::RenderScene()
//
// PROPÓSITO: Genera la imagen
//
void Model3D::RenderScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera->ViewMatrix();
	scene->Draw(program, projection, view);
}

//
// FUNCIÓN: Model3D::TimerAction()
//
// PROPÓSITO: Anima la escena
//
void Model3D::TimerAction()
{
	camera->MoveFront();
}

//
// FUNCIÓN: Model3D::KeyboardAction(int)
//
// PROPÓSITO: respuesta a acciones de teclado
//
void Model3D::KeyboardAction(int virtualKey)
{
	switch (virtualKey)
	{
	case VK_UP:
		camera->TurnDown();
		break;
	case VK_DOWN:
		camera->TurnUp();
		break;
	case VK_LEFT:
		camera->TurnCCW();
		break;
	case VK_RIGHT:
		camera->TurnCW();
		break;
	case 'S':
		camera->SetMoveStep(0.0f);
		break;
	case VK_OEM_PLUS:
		camera->SetMoveStep(camera->GetMoveStep() + 0.1f);
		break;
	case VK_OEM_MINUS:
		camera->SetMoveStep(camera->GetMoveStep() - 0.1f);
		break;
	case 'Q':
		camera->SetMoveStep(0.1f);
		camera->MoveUp();
		camera->SetMoveStep(0.0f);
		break;
	case 'A':
		camera->SetMoveStep(0.1f);
		camera->MoveDown();
		camera->SetMoveStep(0.0f);
		break;
	case 'O':
		camera->SetMoveStep(0.1f);
		camera->MoveLeft();
		camera->SetMoveStep(0.0f);
		break;
	case 'P':
		camera->SetMoveStep(0.1f);
		camera->MoveRight();
		camera->SetMoveStep(0.0f);
		break;
	case 'K':
		camera->TurnLeft();
		break;
	case 'L':
		camera->TurnRight();
		break;
	}
}

//
//  FUNCIÓN: Model3D::MouseAction(int xPos, int yPos, WPARAM wParam)
//
//  PROPÓSITO: respuesta del modelo a un movimiento del ratón.
//
void Model3D::MouseAction(int button, int state, int x, int y)
{
}