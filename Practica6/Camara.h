#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>

enum Vista {};
enum Plano {cenital, picado, normal, contrapicado, nadir};

class Camara
{
	bool profundidad;
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	std::deque<glm::vec3> trail;
	float yaw = -90.0f;
	float pitch = 0.0f;

	Camara(glm::vec3 eye, glm::vec3 front, glm::vec3 up);

	// Actualiza el valor de front en base al pitch y el yaw
	void girar();

	void mirar();

	void cambiarProfundidad();

	void ortogonal();

	void perspectiva();

	void orbital(Plano plano);

	void vista(Vista vista);
};
