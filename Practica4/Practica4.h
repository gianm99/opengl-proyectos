//Practica4.h: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include <stdlib.h>
# define _USE_MATH_DEFINES
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <cmath>
#include <cstdlib>
using namespace std;

// Representa una cámara, con los datos de posicion, dirección, etc.
class Camara
{
public:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	float yaw = -90.0f;
	float pitch = 0.0f;
	// Constructor
	Camara(glm::vec3 eye, glm::vec3 front, glm::vec3 up)
	{
		this->pos = eye;
		this->front = front;
		this->up=up;
	}
};

// Dibuja la escena
void display(void);
// Controla la relación de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void keyboard(unsigned char key, int x, int y);
// Controla el input especial de teclado
void special(int key, int x, int y);
// Anima la escena
void idle(void);
// Dibuja los ejes de coordenadas para poder usarlos como referencia
void referenciaEjes();
// Dibuja los planos formados por la intersección de los ejes de coordenadas 
// para usarlos como referencia
void referenciaPlanos();
// Inicializa algunos valores del dibujado de la escena
void init();
// Cambia a la vista definida por el parámetro cam
void mirar(Camara cam);
// Indican el tamaño inicial de la ventana
const GLsizei windowWidth = 640;
const GLsizei windowHeight = 640;
