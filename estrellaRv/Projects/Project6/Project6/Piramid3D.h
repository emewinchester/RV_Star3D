#ifndef PIRAMID3D_H

#define PIRAMID3D_H

#include <glew.h>
#include "Figure3D.h"

//
// CLASE: Piramid3D
//
// DESCRIPCI�N: Representa una pir�mide de base cuadrada de 
//              lado 2�s y altura 2�s.
// 
class Piramid3D : public Figure3D {
public:
	Piramid3D(GLfloat s);
};


#endif