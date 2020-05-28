#include "stdafx.h"
#include <glew.h>
#include <FreeImage.h>
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
	textureId = 0;
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
// FUNCIÓN: Material::SetTexture(GLuint id)
//
// PROPÓSITO: Asigna el identificador de la textura básica
//
void Material::SetTexture(GLuint id)
{
	textureId = id;
}

//
// FUNCIÓN: Material::GetTexture()
//
// PROPÓSITO: Obtiene el identificador de la textura básica
//
GLuint Material::GetTexture()
{
	return textureId;
}

//
// FUNCIÓN: void Figure3D::InitTexture(GLuint textureId, char* filename)
//
// PROPÓSITO: Carga una textura
//
void Material::InitTexture(char* filename)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	FreeImage_Unload(pImage);
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
	program->SetUniformI("BaseTex", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}