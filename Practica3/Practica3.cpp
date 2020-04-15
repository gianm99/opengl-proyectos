// Practica3.cpp
// Fichero principal
////////////////////////////////////////////////////
#include "Practica3.h"

// Función principal
int main(int argc, char **argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Creamos la ventana
	glutInitWindowSize(WIDTH, HEIGHT);
	// Se situa en el centro de la pantalla
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2);
	// Usamos doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Escena 3D");
	// Indicamos cuales son las funciones de redibujado y reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}

// Función de inicialización de OpenGL
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Función que dibuja la escena
void display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	// set matrix mode
	glMatrixMode(GL_MODELVIEW);
	// clear model view matrix
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,-1.0,1.0);

	// ******
	glPushMatrix();

	glTranslatef(0.0, 0.0, -4.5);

	//ejes(true);
	glBegin(GL_LINES);
	// X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	// Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	// Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();	// Cambiar buffers
	glFlush();
}


void ejes(bool visible)
{
	glPushMatrix();
	glBegin(GL_LINES);
	// X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	// Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	// Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

void planos(bool visible)
{

}

// Función que controla la relación de aspecto
void reshape(GLsizei width, GLsizei height)
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		//gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
		glFrustum(-1.0 ,1.0 ,- 1.0 ,1.0 ,1.5 ,20.0);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		glFrustum(-1.0 ,1.0, -1.0, 1.0, 1.5, 20.0);
	}

}
