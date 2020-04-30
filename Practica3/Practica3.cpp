//Practica3.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include "Practica3.h"

// Indica si está en modo fullscreen
bool fullscreen;
// Indica si los ejes de referencia se tienen que dibujar
bool ejesVisible=true;
// Indica si los planos de referencia se tienen que dibujar
bool planosVisible=true;
// Indica el ángulo de rotación de la tetera
GLfloat angRot = 0.0f;
//Indican los vectores de cada eje para la función de rotación
GLfloat angX;
GLfloat angY;
GLfloat angZ;
const GLfloat incRot = 0.1f;
// Indican las posiciones en los ejes en la que se tiene que dibujar la tetera
GLfloat posX = 0.0f;
GLfloat posY = 0.0f;
GLfloat posZ = 0.0f;
// Indican los incrementos en los ejes en el que las posiciones varian
GLfloat incX;
GLfloat incY;
GLfloat incZ = 0.003f;
//Indican el tamaño inicial de la ventana
GLsizei windowWidth = 640;
GLsizei windowHeight = 640;

void initRandVars() {
	srand(time(NULL));
	angX = (float) 0.1*(rand() % 21 + (-10));
	angY = (float) 0.1*(rand() % 21 + (-10));
	angZ = (float) 0.1*(rand() % 21 + (-10));
	incX = (float) 0.0001*(rand() % 10 + 3);
	srand(time(NULL));
	incY = (float) 0.0001*(rand() % 10 + 3);
	if (rand() % 2 == 1) {
		incX = -incX;
	}
	if (rand() % 2 == 1) {
		incY = -incY;
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(posX,posY,posZ);
	glRotatef(angRot, angX, angY, angZ);
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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:  // Escape
			exit(0);
			break;
		case 'f':
			fullscreen=!fullscreen;
			if (!fullscreen)
			{
				glutReshapeWindow(windowWidth, windowHeight);
				glutPositionWindow(100, 100);
			}
			else
			{
				glutFullScreen();
			}
			break;
		case 'e':
			ejesVisible=!ejesVisible;
			break;
		case 'p':
			planosVisible=!planosVisible;
			break;
	}
}

void idle(void) {
	if (posZ > 0.15f||posZ<-0.15f)
	{
		incZ=-incZ;
	}
	if (posX > 0.93 || posX < -0.93) {
		incX = -incX;
	}
	if (posY > 0.93 || posY < -0.93) {
		incY = -incY;
	}
	posX += incX;
	posY += incY;
	posZ += incZ;
	angRot += incRot;
	glutPostRedisplay();
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
		// X / Y - Rojo 30%
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glVertex3f(0.9f, 0.9f, 0.0f);
		glVertex3f(-0.9f, 0.9f, 0.0f);
		glVertex3f(-0.9f, -0.9f, 0.0f);
		glVertex3f(0.9f, -0.9f, 0.0f);
		// X / Z - Verde 30%
		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glVertex3f(0.9f, 0.0f, 0.9f);
		glVertex3f(-0.9f, 0.0f, 0.9f);
		glVertex3f(-0.9f, 0.0f, -0.9f);
		glVertex3f(0.9f, 0.0f, -0.9f);
		// Y / Z - Azul 30%
		glColor4f(0.0f, 0.0f, 1.0f, 0.3f);
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
	initRandVars();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Escena 3D simple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}