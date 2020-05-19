
#ifndef MODEL3D_H

#define MODEL3D_H

#include <glew.h>
#include <glm/glm.hpp>
#include "Figure3D.h"
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
	Figure3D* fig0;


	GLfloat xAngle;
	GLfloat yAngle;

	glm::mat4 projection;
};

#endif
