#include "Objeto.h"

Objeto::Objeto(Model_OBJ obj, glm::vec3 pos, bool trayectoriaVisible)
{
	this->obj = obj;
	this->pos = pos;
	this->trayectoriaVisible = trayectoriaVisible;
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
	obj.Draw();
	if (trayectoriaVisible)
	{
		dibujarTrayectoria();
	}
	glPopMatrix();
}

void Objeto::guardarTrayectoria()
{
	if (trayectoria.size() == 100)
	{
		trayectoria.pop_front();
	}
	trayectoria.push_back(pos);
}

void Objeto::dibujarTrayectoria()
{
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < trayectoria.size(); i++)
	{
		glVertex3f(trayectoria[i].x, trayectoria[i].y, trayectoria[i].z);
	}
	glEnd();
}

void trazadoElem(std::deque<glm::vec3> pos)
{
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	for (unsigned int i = 0; i < pos.size(); i++)
	{
		glVertex3f(pos[i].x, pos[i].y, pos[i].z);
	}
	glEnd();
	glPopMatrix();
}
