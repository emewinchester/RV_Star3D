#ifndef LIGHT_H

#define LIGHT_H

#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Light {

private:
	glm::vec3 Ldir;	// Light direction
	glm::vec3 La;   // Ambient intensity
	glm::vec3 Ld;   // Difusse intensity
	glm::vec3 Ls;   // Specular intensity

public:
	Light();
	void SetLightDirection(glm::vec3 d);
	void SetAmbientLight(glm::vec3 a);
	void SetDifusseLight(glm::vec3 d);
	void SetSpecularLight(glm::vec3 s);
	void SetUniforms(ShaderProgram* program);
};

#endif