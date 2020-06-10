//Practica3.h: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#pragma once

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <deque>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
class Objeto
{
public:
	glm::vec3 pos;
	glm::vec3 inc;
	float velocidad = 0.1f;
	std::deque<glm::vec3> posiciones;

	// Constructor

	Objeto(glm::vec3 pos, glm::vec3 inc)
	{
		this->pos = pos;
		this->inc = inc;
	}
	void setPos(glm::vec3 posicion) {
		this->pos = pos;
	}

	void setInc(glm::vec3 incremento) {
		this->inc = incremento;
	}

	glm::vec3 getPos() {
		return pos;
	}

	glm::vec3 setInc() {

		return inc;
	}

};

// Dibuja la escena
void display(void);
// Controla la relación de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void keyboard(unsigned char key, int x, int y);
// Anima la escena
void idle(void);
// Dibuja los ejes de coordenadas para poder usarlos como referencia
void referenciaEjes();
// Dibuja los planos formados por la intersección de los ejes de coordenadas 
// para usarlos como referencia
void referenciaPlanos();
// Inicializa algunos valores del dibujado de la escena
void init();
// Funciones de movimiento y dibujado de los objetos
void dibujarTetera();
void dibujarEsfera();
void dibujarCubo();
// Función para el dibujado de la trayectoria
void trazadoElem(std::deque <glm::vec3> pos);
