#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Luz
{
public:
	GLenum id;
	GLfloat *pos;
	GLfloat *direction;
	bool encendida;

	Luz(GLenum id, GLfloat *pos, GLfloat *spot_direction);
	
	Luz();

	void alternar();

	void encender();

	void apagar();

	void mover(glm::vec3 pos);
};
