#include "Camara.h"

// Constructor de Camara
Camara::Camara(glm::vec3 eye, glm::vec3 front, glm::vec3 up)
{
	this->pos = eye;
	this->front = front;
	this->up = up;
	profundidad=true;
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
		gluPerspective(90, 1, 0.1, 100);
	}
	else
	{
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 10.0f);
	}
	girar();
	gluLookAt(pos.x, pos.y, pos.z,
		pos.x + front.x, pos.y + front.y, pos.z + front.z,
		up.x, up.y, up.z);
	glMatrixMode(GL_MODELVIEW);
}

void Camara::cambiarProfundidad()
{
	profundidad=!profundidad;
}

void Camara::ortogonal()
{
	profundidad=false;
}

void Camara::perspectiva()
{
	profundidad=true;
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
	case normal:
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