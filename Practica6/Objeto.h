#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>
#include "Model_OBJ.h"

class Objeto
{
	bool trayectoriaVisible;
public:
	Model_OBJ obj;
	glm::vec3 pos;
	std::deque<glm::vec3> trayectoria;
	Objeto(Model_OBJ obj, glm::vec3 pos, bool trayectoriaVisible);

	Objeto();

	void setTrayectoriaVisible(bool trayectoriaVisible);

	void setPos(glm::vec3 pos);

	glm::vec3 getPos();

	void dibujar();

	void guardarTrayectoria();

	void dibujarTrayectoria();
};