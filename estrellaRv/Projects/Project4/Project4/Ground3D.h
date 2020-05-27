#ifndef GROUND3D_H

#define GROUND3D_H

#include <glew.h>
#include "Figure3D.h"

//
// CLASE: Ground3D
//
// DESCRIPCIÓN: Representa un cuadrado dibujado en el suelo
// 
class Ground3D : public Figure3D {
public:
	Ground3D(GLfloat l1, GLfloat l2);
};


#endif