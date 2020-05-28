#ifndef SCENE3D_H

#define SCENE3D_H

#include <glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Figure3D.h"
#include "Material.h"
#include "Light.h"

class Scene3D {
public:
	Scene3D();
	~Scene3D();
	void Draw(ShaderProgram* program, glm::mat4 proj, glm::mat4 view);

private:
	Figure3D* ground;
	Figure3D* estrella;

	Light* light;
	Material* matg;
	Material* material;
};

#endif