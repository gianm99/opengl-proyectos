//Practica4.h: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include <stdlib.h>
# define _USE_MATH_DEFINES
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <cmath>
#include <cstdlib>
using namespace std;

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
	GLfloat * getEye()
	{
		return eye;
	}
	GLfloat * getCenter()
	{
		return center;
	}
	GLfloat * getUp()
	{
		return up;
	}
	// Setters
	void setEye(GLfloat eyex, GLfloat eyey, GLfloat eyez)
	{
		this->eye[0] = eyex;
		this->eye[1] = eyey;
		this->eye[2] = eyez;
	}
	void setCenter(GLfloat centerx, GLfloat centery, GLfloat centerz)
	{
		this->center[0] = centerx;
		this->center[1] = centery;
		this->center[2] = centerz;
	}
	void setUp(GLfloat upx, GLfloat upy, GLfloat upz)
	{
		this->up[0] = upx;
		this->up[1] = upy;
		this->up[2] = upz;
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
