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
	glm::vec3 Ldir = glm::vec3(1.0f, -0.8f, -1.0f);
	Ldir = glm::normalize(Ldir);
	light = new Light();
	light->SetLightDirection(Ldir);
	light->SetAmbientLight(glm::vec3(0.2f, 0.2f, 0.2f));
	light->SetDifusseLight(glm::vec3(0.8f, 0.8f, 0.8f));
	light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

	matg = new Material();
	matg->SetAmbientReflect(0.0f, 0.6f, 0.0f);
	matg->SetDifusseReflect(0.0f, 0.6f, 0.0f);
	matg->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	matg->SetShininess(16.0f);

	material = new Material();
	material->SetAmbientReflect(1.0f, 0.0f, 0.0f);
	material->SetDifusseReflect(1.0f, 0.0f, 0.0f);
	material->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	material->SetShininess(16.0f);

	ground = new Ground3D(50.0f, 50.0f);
	ground->SetMaterial(matg);


	estrella = new Star3D(5, 4.0f, 12.5f, 2.0f);
	estrella ->SetMaterial(material);
	estrella->Translate(glm::vec3(0.0f, 12.5f, 0.0f));
	estrella->Rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}

//
// FUNCIÓN: Scene3D::~Scene3D()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
Scene3D::~Scene3D()
{
	delete ground;
	delete estrella;
	delete light;
	delete matg;
	delete material;
}

//
// FUNCIÓN: Scene3D::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void Scene3D::Draw(ShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
	light->SetUniforms(program);

	ground->Draw(program, proj, view);


	estrella->Rotate(2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	estrella ->Draw(program, proj, view);
}

