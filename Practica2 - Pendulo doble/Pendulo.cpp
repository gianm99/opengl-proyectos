// Pendulo.cpp++++++++
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int W_WIDTH = 640; // Tamaño incial de la ventana
const int W_HEIGHT = 480;
GLfloat fAnguloCentral = 0.0f, fAnguloInferior = 0.0f; // Ángulos de rotación de los ejes
GLfloat fIncCentral, fIncInferior;
const GLfloat MAX_ANGULO_CENTRAL = 120;
const GLfloat MAX_ANGULO_INFERIOR = 360;

// Función que dibuja la escena
void display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix


	// Parte superior
	glPushMatrix();
	glRotatef(fAnguloCentral, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.992f, 0.968f, 0.003f);	// amarillo
	glVertex3f(-0.01f, 0.0f, 0.0f);		// SUPERIOR IZQUIERDA
	glColor3f(0.121f, 0.992f, 0.058f);	// verde
	glVertex3f(-0.01f, -0.5f, 0.0f);	// INFERIOR IZQUIERDA
	glVertex3f(0.01f, -0.50f, 0.0f);	// INFERIOR DERECHA
	glColor3f(0.992f, 0.968f, 0.003f);	// amarillo
	glVertex3f(0.01f, 0.0f, 0.0f);		// SUPERIOR DERECHA
	glEnd();
	// Parte inferior
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(fAnguloInferior, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.121f, 0.992f, 0.058f);	// verde
	glVertex3f(-0.01f, -0.50f, 0.0f);	// SUPERIOR IZQUIERDA
	glColor3f(0.968f, 0.121f, 0.058f);	// lila
	glVertex3f(-0.01f, -0.95f, 0.0f);	// INFERIOR IZQUIERDA
	glVertex3f(0.01f, -0.95f, 0.0f);	// INFERIOR DERECHA
	glColor3f(0.121f, 0.992f, 0.058f);	// verde
	glVertex3f(0.01f, -0.50f, 0.0f);	// SUPERIOR DERECHA
	glEnd();
	glPopMatrix();

	glutSwapBuffers();	// Cambiar buffers
	glFlush();
}

// Función que permite la animación de la escena
void idle(void)
{
	// Incrementamos los ángulos
	fAnguloCentral += fIncCentral;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloCentral > MAX_ANGULO_CENTRAL || fAnguloCentral < -MAX_ANGULO_CENTRAL)
		fIncCentral = -fIncCentral;

	// Incrementamos los ángulos
	fAnguloInferior += fIncInferior;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloInferior > MAX_ANGULO_INFERIOR)
		fAnguloInferior = 0;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Función que controla la relación de aspecto
void reshape(GLsizei width, GLsizei height)
{
	double left, right, top, bottom, near, far;
	// Calcular el aspect ratio de la nueva ventana
	if (height == 0) height = 1;  // Para evitar dividir por cero
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Hacer que el viewport cubra la nueva ventana
	glViewport(0, 0, width, height);
	// Hacer que el aspect ratio del área de dibujado sea igual al del viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
	}
	else {
		glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

// Función principal
+++