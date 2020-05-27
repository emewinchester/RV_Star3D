#include "stdafx.h"
#include <glew.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera3D.h"

//
// FUNCIÓN: Camera3D::Camera3D()
//
// PROPÓSITO: Construye una cámara
//
// COMENTARIOS: 
//     La posición inicial es (0,0,0).
//     La orientación incial es el sistema de coordenadas del modelo
//     El tamaño del paso inicial es 0.1
//     El támaño del giro inicial es 1.0 grados
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
// FUNCIÓN: Camera3D::ViewMatrix()
//
// PROPÓSITO: Obtiene la matriz View para situar la cámara.
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
// FUNCIÓN: Camera3D::SetPosition(GLfloat x, GLfloat y, GLfloat z)
//
// PROPÓSITO: Asigna la posición de la cámara con respecto al sistema de coordenadas del modelo.
//
void Camera3D::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	Pos = glm::vec3(x, y, z);
}

//
// FUNCIÓN: Camera3D::SetDirection(GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat xUp, GLfloat yUp, GLfloat zUp)
//
// PROPÓSITO: Asigna la orientación de la cámara.
//
void Camera3D::SetDirection(GLfloat xD, GLfloat yD, GLfloat zD, GLfloat xU, GLfloat yU, GLfloat zU)
{
	Dir = glm::vec3(xD, yD, zD);
	Up = glm::vec3(xU, yU, zU);
	Right = glm::cross(Up, Dir);
}

//
// FUNCIÓN: Camera3D::SetMoveStep(GLfloat step)
//
// PROPÓSITO: Asigna el avance en cada paso.
//
void Camera3D::SetMoveStep(GLfloat step)
{
	moveStep = step;
}

//
// FUNCIÓN: Camera3D::SetTurnStep(GLfloat step)
//
// PROPÓSITO: Asigna el ángulo de giro en cada paso.
//
void Camera3D::SetTurnStep(GLfloat step)
{
	turnStep = step;
	cosAngle = (GLfloat)cos(M_PI*turnStep / 180);
	sinAngle = (GLfloat)sin(M_PI*turnStep / 180);
}

//
// FUNCIÓN: Camera3D::GetPosition()
//
// PROPÓSITO: Obtiene la posición de la cámara.
//
glm::vec3 Camera3D::GetPosition()
{
	return Pos;
}

//
// FUNCIÓN: Camera3D::GetDirection()
//
// PROPÓSITO: Obtiene la orientación de la cámara (eje Z).
//
glm::vec3 Camera3D::GetDirection()
{
	return Dir;
}

//
// FUNCIÓN: Camera3D::GetUpDirection()
//
// PROPÓSITO: Obtiene la orientación cenital de la cámara (eje Y).
//
glm::vec3 Camera3D::GetUpDirection()
{
	return Up;
}

//
// FUNCIÓN: Camera3D::GetMoveStep()
//
// PROPÓSITO: Obtiene el avance en cada paso.
//
GLfloat Camera3D::GetMoveStep()
{
	return moveStep;
}

//
// FUNCIÓN: Camera3D::GetTurnStep()
//
// PROPÓSITO: Obtiene el ángulo de giro en cada paso.
//
GLfloat Camera3D::GetTurnStep()
{
	return turnStep;
}

//
// FUNCIÓN: Camera3D::MoveFront()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) en la dirección -Dir 
//
//
void Camera3D::MoveFront()
{
	Pos -= moveStep * Dir;
}

//
// FUNCIÓN: Camera3D::MoveBack()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) hacia atrás en la dirección Dir 
//
//
void Camera3D::MoveBack()
{
	Pos += moveStep * Dir;
}

//
// FUNCIÓN: Camera3D::MoveLeft()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) hacia la izquierda. 
//
//
void Camera3D::MoveLeft()
{
	Pos -= moveStep*Right;
}

//
// FUNCIÓN: Camera3D::MoveRight()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) hacia la derecha. 
//
//
void Camera3D::MoveRight()
{
	Pos += moveStep*Right;
}

//
// FUNCIÓN: Camera3D::MoveUp()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) hacia arriba. 
//
//
void Camera3D::MoveUp()
{
	Pos += moveStep*Up;
}

//
// FUNCIÓN: Camera3D::MoveDown()
//
// PROPÓSITO: Mueve el observador un paso (moveStep) hacia abajo. 
//
void Camera3D::MoveDown()
{
	Pos -= moveStep*Up;
}

//
// FUNCIÓN: Camera3D::TurnRight()
//
// PROPÓSITO: Rota el observador un paso (angleStep) hacia su derecha.
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
// FUNCIÓN: Camera3D::TurnLeft()
//
// PROPÓSITO: Rota el observador un paso (angleStep) hacia su izquierda.
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
// FUNCIÓN: Camera3D::TurnUp()
//
// PROPÓSITO: Rota el observador un paso (angleStep) hacia arriba.
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
// FUNCIÓN: Camera3D::TurnDown()
//
// PROPÓSITO: Rota el observador un paso (angleStep) hacia abajo.
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
// FUNCIÓN: Camera3D::TurnCW()
//
// PROPÓSITO: Rota el observador un paso (angleStep) en sentido del reloj.
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
// FUNCIÓN: Camera3D::TurnDown()
//
// PROPÓSITO: Rota el observador un paso (angleStep) en sentido contrario al reloj.
//
void Camera3D::TurnCCW()
{
	Up.x = cosAngle*Up.x - sinAngle*Right.x;
	Up.y = cosAngle*Up.y - sinAngle*Right.y;
	Up.z = cosAngle*Up.z - sinAngle*Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}