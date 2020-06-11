#include "Objeto.h"

Objeto::Objeto(Model_OBJ obj, glm::vec3 pos, glm::vec3 rot)
{
	this->obj = obj;
	this->pos = pos;
	this->rot = rot;
	trayectoriaVisible = false;
}

Objeto::Objeto() {}

void Objeto::setTrayectoriaVisible(bool trayectoriaVisible)
{
	this->trayectoriaVisible = trayectoriaVisible;
}

void Objeto::setPos(glm::vec3 pos)
{
	this->pos = pos;
}

glm::vec3 Objeto::getPos() {
	return pos;
}

void Objeto::dibujar()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	obj.Draw();
	glPopMatrix();
}

void Objeto::guardarTrayectoria(float rotacionY)
{
	if (trayectoria.size() == 15)
	{
		trayectoria.pop_front();
	}
	trayectoria.push_back(pos);
	if (rotacion.size() == 15)
	{
		rotacion.pop_front();
	}
	rotacion.push_back(rotacionY);
}

void Objeto::cambiarDireccion()
{
	vel.x = -vel.x;
	vel.y = -vel.y;
	vel.z = -vel.z;
}

void Objeto::dibujarTrayectoria()
{
	if (trayectoriaVisible)
	{
		glPushMatrix();
		glLoadIdentity();
		glBegin(GL_LINE_STRIP);
		for (unsigned int i = 0; i < trayectoria.size(); i++)
		{
			glVertex3f(-3.35739994*cos(glm::radians(rotacion[i])), trayectoria[i].y, 3.35739994*sin(glm::radians(rotacion[i])));
		}
		glEnd();
		glPopMatrix();
	}
}

