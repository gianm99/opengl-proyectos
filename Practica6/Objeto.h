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
	glm::vec3 pos; // posición
	glm::vec3 rot; // rotación
	glm::vec3 vel; // velocidad
	std::deque<glm::vec3> trayectoria;
	std::deque<float> rotacion;
	Objeto(Model_OBJ obj, glm::vec3 pos, glm::vec3 rot);

	Objeto();

	void setTrayectoriaVisible(bool trayectoriaVisible);

	void setPos(glm::vec3 pos);

	glm::vec3 getPos();

	void setVel(glm::vec3 vel)
	{
		this->vel = vel;
	}

	void cambiarDireccion();

	void dibujar();

	void guardarTrayectoria(float rotacionY);

	void dibujarTrayectoria();
};