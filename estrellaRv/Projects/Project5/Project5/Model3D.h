
#ifndef MODEL3D_H

#define MODEL3D_H

#include <glew.h>
#include <glm/glm.hpp>
#include "Scene3D.h"
#include "Camera3D.h"
#include "ShaderProgram.h"

class Model3D {
public:
	void Initialize(GLsizei w, GLsizei h);
	void Finalize();
	void RenderScene();
	void KeyboardAction(int virtualKey);
	void MouseAction(int button, int state, int x, int y);
	void TimerAction();
	void ChangeSize(GLsizei w, GLsizei h);

private:
	ShaderProgram* program;
	Scene3D* scene;
	Camera3D* camera;

	glm::mat4 projection;
	glm::mat4 view;
};

#endif
