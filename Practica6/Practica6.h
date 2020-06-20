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
#include "tgload.h"
#define KEY_ESCAPE 27
#define KEY_SPACE 32
#define CFRONT 0
#define CLDER  1
#define CDTR   2
#define CLIZQ  3
#define CSUP   4
#define N_TEXTURAS 5
using namespace std;

// Indican el tamano inicial de la ventana
const GLsizei windowWidth = 720;
const GLsizei windowHeight = 480;
// Indican propiedades de los objetos
const float horseMax = 3.10403f; // altura máxima
const float horseMin = 2.23712f; // altura mínima
// Tipos de proyecciones
enum Proyeccion {normal, caballera, militar};
// Inicializa algunos valores del dibujado de la escena
void init();
// Dibuja la escena
void display(void);
// Anima la escena
void idle(void);
// Controla la relacion de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Controla el input de teclado
void inputKeyboard(unsigned char key, int x, int y);
// Controla el input especial de teclado
void inputSpecialKeyboard(int key, int x, int y);
// Captura los movimientos del ratón para mover la cámara
void inputRaton(int posx, int posy);
// Dibuja los planos y los ejes de referencia
void dibujarReferencia();
// Dibuja el suelo como un tablero de ajedrez
void dibujarSuelo();
// Dibuja el skybox
void dibujarSkyBox(GLuint nro_de_textura);
// Cambia la proyeccion
void initOblicua();
// Inicializa los valores de las luces
void initLuces();
// Inicializa los objetos
void initObjetos();
// Inicializa las texturas
void initTexturas(void);