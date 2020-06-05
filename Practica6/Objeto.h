#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>

class Objeto
{
public:
	glm::vec3 pos;
	glm::vec3 inc;
	float velocidad = 0.1f;
	std::deque<glm::vec3> posiciones;

	Objeto(glm::vec3 pos, glm::vec3 inc);

	Objeto();

	void setPos(glm::vec3 posicion);

	void setInc(glm::vec3 incremento);

	glm::vec3 getPos();

	glm::vec3 setInc();

	void draw();
};