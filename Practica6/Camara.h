#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <deque>
#include <sstream>

enum Vista {alzado, planta, p_izquierdo, p_derecho, isometrica, };
enum Plano {cenital, picado, base, contrapicado, nadir};

class Camara
{
	bool profundidad;
	bool trayectoriaVisible;
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	std::deque<glm::vec3> trayectoria;
	float yaw = -90.0f;
	float pitch = 0.0f;

	Camara(glm::vec3 eye, glm::vec3 front, glm::vec3 up);

	Camara();

	void cambiarTrayectoriaVisible();

	void setTrayectoriaVisible(bool trayectoriaVisible);

	void girar();

	void mirar();

	void cambiarProfundidad();

	void ortogonal();

	void perspectiva();

	void orbital(Plano plano);

	void vista(Vista vista);

	void guardarTrayectoria();

	void dibujarTrayectoria();

	void mostrarCoordenadas(float w, float h);
};
