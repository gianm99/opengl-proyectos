//Practica6.h: Tiovivo
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model_OBJ.h"
#include "Camara.h"
#include "Objeto.h"
#include "Luz.h"
#define KEY_ESCAPE 27
#define KEY_SPACE 32

using namespace std;

// Indican el tamano inicial de la ventana
const GLsizei windowWidth = 640;
const GLsizei windowHeight = 640;
// Indican propiedades de los objetos
const float horseMax = 3.10403f; // altura m�xima
const float horseMin = 2.23712f; // altura m�nima
// Tipos de proyecciones
enum Proyeccion {normal, caballera, militar};
// Dibuja la escena
void display(void);
// Anima la escena
void idle(void);
// Controla la relacion de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void keyboard(unsigned char key, int x, int y);
// Controla el input especial de teclado
void special(int key, int x, int y);
// Dibuja los planos y los ejes de referencia
void referencia();
// Cambia la proyeccion
void proyeccionOblicua();
// Inicializa los valores de las luces
void initLuces();
// Inicializa los objetos
void initObjetos();
// Captura los movimientos del rat�n para mover la c�mara
void camaraRaton(int posx, int posy);
// Inicializa algunos valores del dibujado de la escena
void init();

