//Practica4.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include "Practica4.h"

// Indica si está en fullscreen
bool fullscreen;
// Indica si los ejes de referencia se tienen que dibujar
bool ejesVisible = true;
// Indica si los planos de referencia se tienen que dibujar
bool planosVisible = true;
bool profundidad = true;
// Representa la cámara
Camara cam(0.0f, 0.0f, 1.0f,  // Eye
	0.0f, 0.0f, 0.0f,  // Center 
	0.0f, 1.0f, 0.0f); // Up
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
GLfloat incZ = 0.005f;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Escena 3D simple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(posX, posY, posZ);
	glRotatef(angRot, angX, angY, angZ);
	glutSolidTeapot(0.1f);
	if (ejesVisible) referenciaEjes();
	if (planosVisible) referenciaPlanos();
	glutSwapBuffers();
	glFlush();
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);  // El viewport cubre la ventana
	mirar(cam);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:  // Escape
		exit(0);
		break;
	case 'f':
		fullscreen = !fullscreen;
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
		ejesVisible = !ejesVisible;
		planosVisible = !planosVisible;
		break;
	case 'p':
		profundidad = !profundidad;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (profundidad)
		{
			gluPerspective(90, 1, 0.1, 20);
		}
		else
		{
			glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 10.0f);
		}
		mirar(cam);
		glMatrixMode(GL_MODELVIEW);
		break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key)
	{
		// alzado
	case GLUT_KEY_F1:
		cam.setEye(0.0f, 0.0f, 1.0f);
		cam.setCenter(0.0f, 0.0f, 0.0f);
		cam.setUp(0.0f, 1.0f, 0.0f);
		mirar(cam);
		break;
		// planta
	case GLUT_KEY_F2:
		cam.setEye(0.0f, 1.0f, 0.0f);
		cam.setCenter(0.0f, 0.0f, 0.0f);
		cam.setUp(0.0f, 1.0f, -1.0f);
		mirar(cam);
		break;
		// perfil izquierdo
	case GLUT_KEY_F3:
		cam.setEye(-1.0f, 0.0f, 0.0f);
		cam.setCenter(0.0f, 0.0f, 0.0f);
		cam.setUp(1.0f, 1.0f, 0.0f);
		mirar(cam);
		break;
		// perfil derecho
	case GLUT_KEY_F4:
		cam.setEye(1.0f, 0.0f, 0.0f);
		cam.setCenter(0.0f, 0.0f, 0.0f);
		cam.setUp(1.0f, 1.0f, 0.0f);
		mirar(cam);
		break;
		// isométrica
	case GLUT_KEY_F5:
		break;
		// caballera
	case GLUT_KEY_F6:
		break;
		// militar
	case GLUT_KEY_F7:
		break;
	}
}

void idle(void) {
	if (posZ > 0.7f || posZ < -0.7f)
	{
		incZ = -incZ;
	}
	if (posX > 0.7f || posX < -0.7f) {
		incX = -incX;
	}
	if (posY > 0.7f || posY < -0.7f) {
		incY = -incY;
	}
	posX += incX;
	posY += incY;
	posZ += incZ;
	glutPostRedisplay();
}

void mirar(Camara cam)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (profundidad)
	{
		gluPerspective(90, 1, 0.1, 20);
	}
	else
	{
		glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 10.0f);
	}
	gluLookAt(cam.getEye()[0], cam.getEye()[1], cam.getEye()[2],
		cam.getCenter()[0], cam.getCenter()[0], cam.getCenter()[0],
		cam.getUp()[0], cam.getUp()[1], cam.getUp()[2]);
	glMatrixMode(GL_MODELVIEW);
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

