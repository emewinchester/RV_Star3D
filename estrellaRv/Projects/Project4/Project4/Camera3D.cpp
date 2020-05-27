#include "stdafx.h"
#include <glew.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera3D.h"

//
// FUNCI�N: Camera3D::Camera3D()
//
// PROP�SITO: Construye una c�mara
//
// COMENTARIOS: 
//     La posici�n inicial es (0,0,0).
//     La orientaci�n incial es el sistema de coordenadas del modelo
//     El tama�o del paso inicial es 0.1
//     El t�ma�o del giro inicial es 1.0 grados
//
Camera3D::Camera3D() {
	Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Dir = glm::vec3(0.0f, 0.0f, 1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);

	moveStep = 0.1f;
	turnStep = 1.0f;
	cosAngle = (GLfloat)cos(M_PI*turnStep / 180);
	sinAngle = (GLfloat)sin(M_PI*turnStep / 180);
}

//
// FUNCI�N: Camera3D::ViewMatrix()
//
// PROP�SITO: Obtiene la matriz View para situar la c�mara.
//
glm::mat4 Camera3D::ViewMatrix()
{
	// Creates a rotation matrix using vectors Dir, Up and Right
	glm::mat4 matrix(1.0f);
	matrix[0][0] = Right.x;
	matrix[1][0] = Right.y;
	matrix[2][0] = Right.z;
	matrix[3][0] = 0.0f;
	matrix[0][1] = Up.x;
	matrix[1][1] = Up.y;
	matrix[2][1] = Up.z;
	matrix[3][1] = 0.0f;
	matrix[0][2] = Dir.x;
	matrix[1][2] = Dir.y;
	matrix[2][2] = Dir.z;
	matrix[3][2] = 0.0f;
	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
	matrix[3][3] = 1.0f;

	return glm::translate(matrix, -Pos);
}

//
// FUNCI�N: Camera3D::SetPosition(GLfloat x, GLfloat y, GLfloat z)
//
// PROP�SITO: Asigna la posici�n de la c�mara con respecto al sistema de coordenadas del modelo.
//
void Camera3D::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	Pos = glm::vec3(x, y, z);
}

//
// FUNCI�N: Camera3D::SetDirection(GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat xUp, GLfloat yUp, GLfloat zUp)
//
// PROP�SITO: Asigna la orientaci�n de la c�mara.
//
void Camera3D::SetDirection(GLfloat xD, GLfloat yD, GLfloat zD, GLfloat xU, GLfloat yU, GLfloat zU)
{
	Dir = glm::vec3(xD, yD, zD);
	Up = glm::vec3(xU, yU, zU);
	Right = glm::cross(Up, Dir);
}

//
// FUNCI�N: Camera3D::SetMoveStep(GLfloat step)
//
// PROP�SITO: Asigna el avance en cada paso.
//
void Camera3D::SetMoveStep(GLfloat step)
{
	moveStep = step;
}

//
// FUNCI�N: Camera3D::SetTurnStep(GLfloat step)
//
// PROP�SITO: Asigna el �ngulo de giro en cada paso.
//
void Camera3D::SetTurnStep(GLfloat step)
{
	turnStep = step;
	cosAngle = (GLfloat)cos(M_PI*turnStep / 180);
	sinAngle = (GLfloat)sin(M_PI*turnStep / 180);
}

//
// FUNCI�N: Camera3D::GetPosition()
//
// PROP�SITO: Obtiene la posici�n de la c�mara.
//
glm::vec3 Camera3D::GetPosition()
{
	return Pos;
}

//
// FUNCI�N: Camera3D::GetDirection()
//
// PROP�SITO: Obtiene la orientaci�n de la c�mara (eje Z).
//
glm::vec3 Camera3D::GetDirection()
{
	return Dir;
}

//
// FUNCI�N: Camera3D::GetUpDirection()
//
// PROP�SITO: Obtiene la orientaci�n cenital de la c�mara (eje Y).
//
glm::vec3 Camera3D::GetUpDirection()
{
	return Up;
}

//
// FUNCI�N: Camera3D::GetMoveStep()
//
// PROP�SITO: Obtiene el avance en cada paso.
//
GLfloat Camera3D::GetMoveStep()
{
	return moveStep;
}

//
// FUNCI�N: Camera3D::GetTurnStep()
//
// PROP�SITO: Obtiene el �ngulo de giro en cada paso.
//
GLfloat Camera3D::GetTurnStep()
{
	return turnStep;
}

//
// FUNCI�N: Camera3D::MoveFront()
//
// PROP�SITO: Mueve el observador un paso (moveStep) en la direcci�n -Dir 
//
//
void Camera3D::MoveFront()
{
	Pos -= moveStep * Dir;
}

//
// FUNCI�N: Camera3D::MoveBack()
//
// PROP�SITO: Mueve el observador un paso (moveStep) hacia atr�s en la direcci�n Dir 
//
//
void Camera3D::MoveBack()
{
	Pos += moveStep * Dir;
}

//
// FUNCI�N: Camera3D::MoveLeft()
//
// PROP�SITO: Mueve el observador un paso (moveStep) hacia la izquierda. 
//
//
void Camera3D::MoveLeft()
{
	Pos -= moveStep*Right;
}

//
// FUNCI�N: Camera3D::MoveRight()
//
// PROP�SITO: Mueve el observador un paso (moveStep) hacia la derecha. 
//
//
void Camera3D::MoveRight()
{
	Pos += moveStep*Right;
}

//
// FUNCI�N: Camera3D::MoveUp()
//
// PROP�SITO: Mueve el observador un paso (moveStep) hacia arriba. 
//
//
void Camera3D::MoveUp()
{
	Pos += moveStep*Up;
}

//
// FUNCI�N: Camera3D::MoveDown()
//
// PROP�SITO: Mueve el observador un paso (moveStep) hacia abajo. 
//
void Camera3D::MoveDown()
{
	Pos -= moveStep*Up;
}

//
// FUNCI�N: Camera3D::TurnRight()
//
// PROP�SITO: Rota el observador un paso (angleStep) hacia su derecha.
//
void Camera3D::TurnRight()
{
	Dir.x = cosAngle*Dir.x - sinAngle*Right.x;
	Dir.y = cosAngle*Dir.y - sinAngle*Right.y;
	Dir.z = cosAngle*Dir.z - sinAngle*Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

//
// FUNCI�N: Camera3D::TurnLeft()
//
// PROP�SITO: Rota el observador un paso (angleStep) hacia su izquierda.
//
void Camera3D::TurnLeft()
{
	Dir.x = cosAngle*Dir.x + sinAngle*Right.x;
	Dir.y = cosAngle*Dir.y + sinAngle*Right.y;
	Dir.z = cosAngle*Dir.z + sinAngle*Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

//
// FUNCI�N: Camera3D::TurnUp()
//
// PROP�SITO: Rota el observador un paso (angleStep) hacia arriba.
//
void Camera3D::TurnUp()
{
	Dir.x = cosAngle*Dir.x - sinAngle*Up.x;
	Dir.y = cosAngle*Dir.y - sinAngle*Up.y;
	Dir.z = cosAngle*Dir.z - sinAngle*Up.z;

	// Up = Dir x Right
	Up = glm::cross(Dir, Right);
}

//
// FUNCI�N: Camera3D::TurnDown()
//
// PROP�SITO: Rota el observador un paso (angleStep) hacia abajo.
//
void Camera3D::TurnDown()
{
	Dir.x = cosAngle*Dir.x + sinAngle*Up.x;
	Dir.y = cosAngle*Dir.y + sinAngle*Up.y;
	Dir.z = cosAngle*Dir.z + sinAngle*Up.z;

	// Up = Dir x Right
	Up = glm::cross(Dir, Right);
}

//
// FUNCI�N: Camera3D::TurnCW()
//
// PROP�SITO: Rota el observador un paso (angleStep) en sentido del reloj.
//
void Camera3D::TurnCW()
{
	Up.x = cosAngle*Up.x + sinAngle*Right.x;
	Up.y = cosAngle*Up.y + sinAngle*Right.y;
	Up.z = cosAngle*Up.z + sinAngle*Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

//
// FUNCI�N: Camera3D::TurnDown()
//
// PROP�SITO: Rota el observador un paso (angleStep) en sentido contrario al reloj.
//
void Camera3D::TurnCCW()
{
	Up.x = cosAngle*Up.x - sinAngle*Right.x;
	Up.y = cosAngle*Up.y - sinAngle*Right.y;
	Up.z = cosAngle*Up.z - sinAngle*Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}