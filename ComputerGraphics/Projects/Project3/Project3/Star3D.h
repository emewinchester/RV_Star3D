#ifndef STAR3D_H

#define STAR3D_H

#include <glew.h>
#include "Figure3D.h"

//
// CLASE: Star3D
//
// DESCRIPCIÓN: Representa una estrella de p puntas, de radio interior
// radioInterior, radio exterior radioExterior y ancho 2*ancho 
//             
// 
class Star3D : public Figure3D {
public:
	Star3D(GLint puntas, GLfloat radioInterior, GLfloat radioExterior, GLfloat ancho);
};


#endif
