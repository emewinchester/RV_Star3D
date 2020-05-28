#include "stdafx.h"
#include <glew.h>
#include "Material.h"

//
// FUNCIÓN: Material::Material()
//
// PROPÓSITO: Construye un material con los valores por defecto
//
Material::Material()
{
	Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	Shininess = 16.0f;
}

//
// FUNCIÓN: Material::SetAmbientReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROPÓSITO: Asigna la reflectividad ambiental (color ante la luz ambiental)
//
void Material::SetAmbientReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Ka = glm::vec3(r, g, b);
}

//
// FUNCIÓN: Material::SetDifusseReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROPÓSITO: Asigna la reflectividad difusa (color ante la luz difusa)
//
void Material::SetDifusseReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Kd = glm::vec3(r, g, b);
}

//
// FUNCIÓN: Material::SetSpecularReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROPÓSITO: Asigna la reflectividad especular (color ante la luz especular)
//
void Material::SetSpecularReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Ks = glm::vec3(r, g, b);
}

//
// FUNCIÓN: Material::SetShininess(GLfloat f)
//
// PROPÓSITO: Asigna el factor de brillo (comportamiento ante la luz especular)
//
void Material::SetShininess(GLfloat f)
{
	Shininess = f;
}


//
// FUNCIÓN: Material::SetUniforms(ShaderProgram* program)
//
// PROPÓSITO: Configura las propiedades de material en el programa gráfico
//
void Material::SetUniforms(ShaderProgram* program)
{
	program->SetUniformVec3("Material.Ka", Ka);
	program->SetUniformVec3("Material.Kd", Kd);
	program->SetUniformVec3("Material.Ks", Ks);
	program->SetUniformF("Material.Shininess", Shininess);
}