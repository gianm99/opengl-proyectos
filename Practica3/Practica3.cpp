//Practica3.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <iostream>

// Dibuja la escena
void display(void);
// Controla la relación de aspecto de la escena
void reshape(GLsizei width, GLsizei height);
// Anima la escena
void idle(void);
// Dibuja los ejes de coordenadas para poder usarlos como referencia
void referenciaEjes();
// Dibuja los planos formados por la intersección de los ejes de coordenadas 
// para usarlos como referencia
void referenciaPlanos();
// Inicializa algunos valores del dibujado de la escena
void init();

// Indica si los ejes de referencia se tienen que dibujar
bool ejesVisible;
// Indica si los planos de referencia se tienen que dibujar
bool planosVisible;
// Indica la posición en el eje Z en la que se tiene que dibujar la tetera
GLfloat posZ=0.0f;
// Indica el incremento en el eje Z en el que posZ varia
GLfloat incZ = 0.003f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f,0.0f,posZ);
	glRotatef(45.0f, 0.0f, 0.7f, 1.0f);
	glutSolidTeapot(0.1f);
	if (ejesVisible)referenciaEjes();
	if (planosVisible)referenciaPlanos();
	glutSwapBuffers();
	glFlush();
}

void reshape(GLsizei width, GLsizei height)
{
	// Calcular el aspect ratio de la nueva ventana
	if (height == 0) height = 1;  // Para evitar dividir por cero
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Hacer que el viewport cubra la nueva ventana
	glViewport(0, 0, width, height);
	// Hacer que el aspect ratio del área de dibujado sea igual al del viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		glFrustum(1.0 * aspect, 1.0 * aspect, 1.0, 1.0, 2.0, 2.0);
	}
	else {
		glFrustum(1.0, 1.0, 1.0 / aspect, 1.0 / aspect, 2.0, 2.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
	if (posZ > 0.15f||posZ<-0.15f)
	{
		incZ=-incZ;
	}
	posZ+=incZ;
	glutPostRedisplay();
}

void preguntarVisibilidad()
{
	char eleccion;
	while (true)
	{
		std::cout << "Quieres que los ejes de referencia sean visibles? (s/n)" << std::endl;
		std::cin >> eleccion;
		if (eleccion == 's')
		{
			ejesVisible=true;
			break;
		}
		else if(eleccion=='n')
		{
			ejesVisible=false;
			break;
		}
		else
		{
			std::cout << "Por favor responde con 's' o 'n'." << std::endl;
		}
	}
	while (true)
	{
		std::cout << "Quieres que los planos de referencia sean visibles? (s/n)" << std::endl;
		std::cin >> eleccion;
		if (eleccion == 's')
		{
			planosVisible = true;
			return;
		}
		else if (eleccion == 'n')
		{
			planosVisible = false;
			return;
		}
		else
		{
			std::cout << "Por favor responde con 's' o 'n'." << std::endl;
		}
	}
}

void referenciaEjes()
{
	glLoadIdentity();
	glBegin(GL_LINES);
		// X
		glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
		glVertex3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		// Y
		glColor3f(0.0f, 1.0f, 0.0f);  // Verde
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		// Z
		glColor3f(0.0f, 0.0f, 1.0f);  // Azul
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();
}

void referenciaPlanos()
{
	glLoadIdentity();
	glBegin(GL_QUADS);
		// X / Y - Rojo 60%
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glVertex3f(0.9f, 0.9f, 0.0f);
		glVertex3f(-0.9f, 0.9f, 0.0f);
		glVertex3f(-0.9f, -0.9f, 0.0f);
		glVertex3f(0.9f, -0.9f, 0.0f);
		// X / Z - Verde 60%
		glColor4f(0.0f, 1.0f, 0.0f, 0.6f);
		glVertex3f(0.9f, 0.0f, 0.9f);
		glVertex3f(-0.9f, 0.0f, 0.9f);
		glVertex3f(-0.9f, 0.0f, -0.9f);
		glVertex3f(0.9f, 0.0f, -0.9f);
		// Y / Z - Azul 60%
		glColor4f(0.0f, 0.0f, 1.0f, 0.6f);
		glVertex3f(0.0f, 0.9f, 0.9f);
		glVertex3f(0.0f, -0.9f, 0.9f);
		glVertex3f(0.0f, -0.9f, -0.9f);
		glVertex3f(0.0f, 0.9f, -0.9f);
	glEnd();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);
	glutCreateWindow("Escena 3D simple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	// Preguntar al usuario si hay que dibujar los ejes y planos
	preguntarVisibilidad();
	glutMainLoop();
	return 0;
}