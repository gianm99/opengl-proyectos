#include "Camara.h"

// Constructor de Camara
Camara::Camara(glm::vec3 eye, glm::vec3 front, glm::vec3 up)
{
	this->pos = eye;
	this->front = front;
	this->up = up;
	profundidad = true;
	trayectoriaVisible = false;
}

Camara::Camara() {}

void Camara::cambiarTrayectoriaVisible()
{
	trayectoriaVisible = !trayectoriaVisible;
}

void Camara::setTrayectoriaVisible(bool trayectoriaVisible)
{
	this->trayectoriaVisible = trayectoriaVisible;
}

void Camara::girar()
{
	if (pitch > 89.999f)
	{
		pitch = 89.999f;
	}
	else if (pitch > 89.999f)
	{
		pitch = -89.999f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
}

void Camara::mirar()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (profundidad)
	{
		gluPerspective(60, 1.778, 0.1, 200);
	}
	else
	{
		glOrtho(-17.778f, 17.778f, -10.0f, 10.0f, -10.0f, 200.0f);
	}
	girar();
	gluLookAt(pos.x, pos.y, pos.z,
		pos.x + front.x, pos.y + front.y, pos.z + front.z,
		up.x, up.y, up.z);
	glMatrixMode(GL_MODELVIEW);
}

void Camara::cambiarProfundidad()
{
	profundidad = !profundidad;
}

void Camara::ortogonal()
{
	profundidad = false;

}

void Camara::perspectiva()
{
	profundidad = true;
}

void Camara::vista(Vista vista)
{
	switch (vista)
	{
	case alzado:
		pos = glm::vec3(0.0f, 5.0f, 15.0f);
		yaw = -90.0f;
		pitch = 0.0f;
		mirar();
		break;
	case planta:
		pos = glm::vec3(0.0f, 15.0f, 0.0f);
		yaw = -90.0f;
		pitch = -90.0f;
		mirar();
		break;
	case p_izquierdo:
		pos = glm::vec3(-15.0f, 5.0f, 0.0f);
		yaw = 0.0f;
		pitch = 0.0f;
		mirar();
		break;
	case p_derecho:
		pos = glm::vec3(15.0f, 5.0f, 0.0f);
		yaw = 180.0f;
		pitch = 0.0f;
		mirar();
		break;
	case isometrica:
		pos = glm::vec3(15.0f, 15.0f, 15.0f);
		yaw = -135.0f;
		pitch = -glm::degrees(asin(1 / sqrt(3)));
		mirar();
		break;
	}
}

void Camara::orbital(Plano plano)
{
	float pitch_rotation = 0.0f;
	glm::mat4 rotate_yaw_matrix = glm::mat4(1.f);
	glm::mat4 m = glm::mat4(1.f); // Matriz para calculos
	switch (plano)
	{
		// Plano cenital
	case cenital:
		pitch_rotation = -89.999f - pitch;
		right = glm::normalize(glm::cross(front, up));
		m = glm::rotate(m, glm::radians(pitch_rotation), right);
		pos = glm::vec3(m * glm::vec4(-front, 0.0f)) + pos + front;
		pitch = -89.999f;
		mirar();
		break;
		// Plano picado
	case picado:
		pitch_rotation = -45.0f - pitch;
		right = glm::normalize(glm::cross(front, up));
		m = glm::rotate(m, glm::radians(pitch_rotation), right);
		pos = glm::vec3(m * glm::vec4(-front, 0.0f)) + pos + front;
		pitch = -45.0f;
		mirar();
		break;
		// Plano normal
	case base:
		pitch_rotation = -pitch;
		right = glm::normalize(glm::cross(front, up));
		m = glm::rotate(m, glm::radians(pitch_rotation), right);
		pos = glm::vec3(m * glm::vec4(-front, 0.0f)) + pos + front;
		pitch = 0.0f;
		mirar();
		break;
		// Plano contrapicado
	case contrapicado:
		pitch_rotation = 45.0f - pitch;
		right = glm::normalize(glm::cross(front, up));
		m = glm::rotate(m, glm::radians(pitch_rotation), right);
		pos = glm::vec3(m * glm::vec4(-front, 0.0f)) + pos + front;
		pitch = 45.0f;
		mirar();
		break;
		// Plano nadir
	case nadir:
		pitch_rotation = 89.999f - pitch;
		right = glm::normalize(glm::cross(front, up));
		m = glm::rotate(m, glm::radians(pitch_rotation), right);
		pos = glm::vec3(m * glm::vec4(-front, 0.0f)) + pos + front;
		pitch = 89.999f;
		mirar();
		break;
	}
}

void Camara::guardarTrayectoria()
{
	if (trayectoria.size() == 100)
	{
		trayectoria.pop_front();
	}
	trayectoria.push_back(pos);
}

void Camara::dibujarTrayectoria()
{
	if (trayectoriaVisible)
	{
		glPushMatrix();
		glBegin(GL_LINE_STRIP);
		for (unsigned int i = 0; i < trayectoria.size(); i++)
		{
			glVertex3f(trayectoria[i].x, trayectoria[i].y, trayectoria[i].z);
		}
		glEnd();
		glPopMatrix();
	}
}

void Camara::mostrarCoordenadas(float w, float h) {
	std::ostringstream x, y, z;
	x << pos.x;
	y << pos.y;
	z << pos.z;
	std::string s = "X: ";
	s += x.str();
	s += " Y: ";
	s += y.str();
	s += " Z: ";
	s += z.str();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);//needs to be called before RasterPos
	glRasterPos2i(10, 10);
	void * font = GLUT_BITMAP_9_BY_15;

	for (std::string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}