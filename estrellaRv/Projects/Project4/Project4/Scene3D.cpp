#include "stdafx.h"
#include <glew.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene3D.h"
#include "ShaderProgram.h"
#include "Figure3D.h"
#include "Ground3D.h"
#include "Star3D.h"


//
// FUNCIÓN: Scene3D::Scene3D()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
Scene3D::Scene3D()
{
	ground = new Ground3D(50.0f, 50.0f);


	// Dibujamos la estrella

	fig0 = new Star3D(5, 4.0f, 12.5f, 3.0f);
	//Star3D(GLint puntas, GLfloat radioInterior, GLfloat radioExterior, GLfloat ancho);


	// Desplazamiento de la figura respecto del centro del mundo
	//                         x       y     z
	fig0->Translate(glm::vec3(0.0f, 12.5f, 0.0f));
	// Gira la figura con respecto al sistema de coordenadas del mundo
	// optativo  giro en grados		x     y      z   (eje que giro)
	//fig0->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
}

//
// FUNCIÓN: Scene3D::~Scene3D()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
Scene3D::~Scene3D()
{
	delete ground;
	delete fig0;
	
}

//
// FUNCIÓN: Scene3D::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void Scene3D::Draw(ShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
	fig0->Rotate(5.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	ground->Draw(program, proj, view);
	fig0->Draw(program, proj, view);
}

