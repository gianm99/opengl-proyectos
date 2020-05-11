//Practica4.h: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include <stdlib.h>

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// Dibuja la escena
void display(void);
// Controla la relaci�n de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void keyboard(unsigned char key, int x, int y);
// Anima la escena
void idle(void);
// Dibuja los ejes de coordenadas para poder usarlos como referencia
void referenciaEjes();
// Dibuja los planos formados por la intersecci�n de los ejes de coordenadas 
// para usarlos como referencia
void referenciaPlanos();
// Inicializa algunos valores del dibujado de la escena
void init();
// Inicializa los valores globales que necesitan de una funci�n de generaci�n 
// aleatoria de n�meros
void initRandVars();
void camaraFunc();

//Indican el tama�o inicial de la ventana
const GLsizei windowWidth = 640;
const GLsizei windowHeight = 640;