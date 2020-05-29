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
	matg->InitTexture("textures/stone.jpg");

	GLuint textureId = matg->GetTexture();

	ground = new Ground3D(50.0f, 50.0f);
	//ground->Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//ground->Translate(glm::vec3(0.0f, -300.0f, -20.0f));
	ground->SetMaterial(matg);

	mat0 = new Material();
	mat0->SetAmbientReflect(1.0f, 0.0f, 1.0f);
	mat0->SetDifusseReflect(1.0f, 0.0f, 1.0f);
	mat0->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat0->SetShininess(16.0f);
	mat0->SetTexture(textureId);



	mat1 = new Material();
	mat1->SetAmbientReflect(1.0f, 1.0f, 1.0f);
	mat1->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mat1->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat1->SetShininess(16.0f);
	mat1->SetTexture(textureId);



	mat2 = new Material();
	mat2->SetAmbientReflect(0.2f, 0.2f, 1.0f);
	mat2->SetDifusseReflect(0.2f, 0.2f, 1.0f);
	mat2->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat2->SetShininess(16.0f);
	mat2->SetTexture(textureId);



	mat3 = new Material();
	mat3->SetAmbientReflect(1.0f, 0.0f, 0.0f);
	mat3->SetDifusseReflect(1.0f, 0.0f, 0.0f);
	mat3->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat3->SetShininess(16.0f);
	mat3->SetTexture(textureId);



	mat4 = new Material();
	mat4->SetAmbientReflect(1.0f, 1.0f, 0.0f);
	mat4->SetDifusseReflect(1.0f, 1.0f, 0.0f);
	mat4->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat4->SetShininess(16.0f);
	mat4->SetTexture(textureId);



	mat5 = new Material();
	mat5->SetAmbientReflect(0.0f, 1.0f, 1.0f);
	mat5->SetDifusseReflect(0.0f, 1.0f, 1.0f);
	mat5->SetSpecularReflect(0.8f, 0.8f, 0.8f);
	mat5->SetShininess(16.0f);
	mat5->SetTexture(textureId);



	matEstrella = new Material();
	matEstrella->SetAmbientReflect(0.917f, 0.745f, 0.247f); // afecta al color
	matEstrella->SetDifusseReflect(0.917f, 0.745f, 0.247f); //
	matEstrella->SetSpecularReflect(0.8f, 0.8f, 0.8f); // el especular no modifica el color
	matEstrella->SetShininess(16.0f);
	matEstrella->InitTexture("textures/dorado.jpg");

	textureId = matEstrella->GetTexture();

	estrella = new Star3D(5, 4.0f, 12.5f, 2.0f);
	estrella->SetMaterial(matEstrella);
	estrella->Translate(glm::vec3(0.0f, 12.0f, -0.0f));
	//estrella->Rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

//
// FUNCIÓN: Scene3D::~Scene3D()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
Scene3D::~Scene3D()
{
	delete ground;

	delete matg;
	delete mat0;
	delete mat1;
	delete mat2;
	delete mat3;
	delete mat4;
	delete mat5;
	delete light;
	delete estrella;
	delete matEstrella;
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

	//estrella->Rotate(2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	estrella->Draw(program, proj, view);
}

