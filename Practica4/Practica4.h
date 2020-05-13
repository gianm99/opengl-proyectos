//Practica4.h: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include <stdlib.h>

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

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
// Inicializa los valores globales que necesitan de una función de generación 
// aleatoria de números
void initRandVars();
// Cambia a la vista definida por el parámetro vista
void vistaFija(int vista);
// Indican el tamaño inicial de la ventana
const GLsizei windowWidth = 640;
const GLsizei windowHeight = 640;
// Indica el número de vistas fijas disponibles
const int nvistas = 7;

// Representa una cámara, con los datos de posicion, dirección, etc.
class Camara
{
	GLfloat eye[3];
	GLfloat center[3];
	GLfloat up[3];
public:
	// Constructor
	Camara(GLfloat eyex, GLfloat eyey, GLfloat eyez,
		GLfloat centerx, GLfloat centery, GLfloat centerz,
		GLfloat upx, GLfloat upy, GLfloat upz)
	{
		eye[0] = eyex;
		eye[1] = eyey;
		eye[2] = eyez;
		center[0] = centerx;
		center[1] = centery;
		center[2] = centerz;
		up[0] = upx;
		up[1] = upy;
		up[2] = upz;
	}
	// Getters
	GLfloat getEye(int i)
	{
		return eye[i];
	}
	GLfloat getCenter(int i)
	{
		return center[i];
	}
	GLfloat getUp(int i)
	{
		return up[i];
	}
	// Setters
	void setEye(int i, GLfloat eye)
	{
		this->eye[i] = eye;
	}
	void setCenter(int i, GLfloat center)
	{
		this->center[i] = center;
	}
	void setUp(int i, GLfloat up)
	{
		this->up[i] = up;
	}

};
