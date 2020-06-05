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

enum Proyeccion {normal, caballera, militar};

// Dibuja la escena
void display(void);
// Controla la relacion de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void keyboard(unsigned char key, int x, int y);
// Controla el input especial de teclado
void special(int key, int x, int y);
// Anima la escena
void idle(void);
// Dibuja los planos y los ejes de referencia
void referencia();
// Inicializa algunos valores del dibujado de la escena
void init();
// Cambia a la vista definida por el parametro cam
void look(Camara cam);
// Inicializa los valores de las luces
void configurarLuces();
// Funciones de movimiento y dibujado de los objetos
void dibujarTetera();
void dibujarEsfera();
void dibujarCubo();
// Función para el dibujado de la trayectoria
void trazadoElem(std::deque <glm::vec3> pos);
// Modifica la matriz para que la vista sea oblicua
void proyeccionOblicua();
// Inicializa los objetos
void inicializarObjetos();