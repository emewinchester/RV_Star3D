#include "stdafx.h"
#include <glew.h>
#include "Material.h"

//
// FUNCI�N: Material::Material()
//
// PROP�SITO: Construye un material con los valores por defecto
//
Material::Material()
{
	Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	Shininess = 16.0f;
}

//
// FUNCI�N: Material::SetAmbientReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROP�SITO: Asigna la reflectividad ambiental (color ante la luz ambiental)
//
void Material::SetAmbientReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Ka = glm::vec3(r, g, b);
}

//
// FUNCI�N: Material::SetDifusseReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROP�SITO: Asigna la reflectividad difusa (color ante la luz difusa)
//
void Material::SetDifusseReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Kd = glm::vec3(r, g, b);
}

//
// FUNCI�N: Material::SetSpecularReflect(GLfloat r, GLfloat g, GLfloat b)
//
// PROP�SITO: Asigna la reflectividad especular (color ante la luz especular)
//
void Material::SetSpecularReflect(GLfloat r, GLfloat g, GLfloat b)
{
	Ks = glm::vec3(r, g, b);
}

//
// FUNCI�N: Material::SetShininess(GLfloat f)
//
// PROP�SITO: Asigna el factor de brillo (comportamiento ante la luz especular)
//
void Material::SetShininess(GLfloat f)
{
	Shininess = f;
}


//
// FUNCI�N: Material::SetUniforms(ShaderProgram* program)
//
// PROP�SITO: Configura las propiedades de material en el programa gr�fico
//
void Material::SetUniforms(ShaderProgram* program)
{
	program->SetUniformVec3("Material.Ka", Ka);
	program->SetUniformVec3("Material.Kd", Kd);
	program->SetUniformVec3("Material.Ks", Ks);
	program->SetUniformF("Material.Shininess", Shininess);
}