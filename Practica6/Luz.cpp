#include "Luz.h"
GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

Luz::Luz(GLenum id, GLfloat *pos, GLfloat *spot_direction)
{
	this->id = id;
	this->pos = pos;
	this->direction = spot_direction;
	this->encendida = true;
	glLightfv(id, GL_POSITION, pos);
	glLightfv(id, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(id, GL_AMBIENT, ambient);
	glLightfv(id, GL_DIFFUSE, diffuse);
	glLightfv(id, GL_SPECULAR, specular);
}

Luz::Luz() {}

void Luz::alternar()
{
	encendida=!encendida;
	if (encendida)
	{
		encender();
	}
	else
	{
		apagar();
	}
}

void Luz::encender()
{
	glEnable(id);
}

void Luz::apagar()
{
	glDisable(id);
}

void Luz::mover(glm::vec3 pos)
{
	GLfloat buffer[] ={pos.x,pos.y,pos.z,1.0f};
	glLightfv(id, GL_POSITION, buffer);
}
