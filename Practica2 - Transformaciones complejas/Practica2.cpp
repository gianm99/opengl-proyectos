// Practica2.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tamano incial de la ventana
const int W_HEIGHT = 500;

// Funcion que controla la proporcion al cambiar el tamano
void reshape(int width, int height)
{
	const float ar_origin = (float)W_WIDTH / (float)W_HEIGHT;
	const float ar_new = (float)width / (float)height;

	float scale_w = (float)width / (float)W_WIDTH;
	float scale_h = (float)height / (float)W_HEIGHT;
	if (ar_new > ar_origin) {
		scale_w = scale_h;
	}
	else {
		scale_h = scale_w;
	}

	float margin_x = (width - W_WIDTH * scale_w) / 2;
	float margin_y = (height - W_HEIGHT * scale_h) / 2;

	glViewport(margin_x, margin_y, W_WIDTH * scale_w, W_HEIGHT * scale_h);
}

// Funcion que visualiza la escena OpenGL
void display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

									 /*A continuacion dibujamos los dos cuadrados sobre los que vamos a realizar
									 transformaciones compuestas*/

									 // Rotacion sobre el centro del cuadrado
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.5f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.73f, 0.17f, 0.15f);	// rojo
	glVertex3f(-0.65f, 0.15f, 0.0f);	// arriba-izquierda
	glVertex3f(-0.65f, -0.15f, 0.0f);	// abajo-izquierda
	glColor3f(.08f, 0.4f, 0.75f);		// azul
	glVertex3f(-0.35f, -0.15f, 0.0f);	// abajo-derecha
	glVertex3f(-0.35f, 0.15f, 0.0f);	// arriba-derecha
	glEnd();
	glLoadIdentity();

	// Escalado sobre la esquina inferior derecha del cuadrado
	glTranslatef(0.65f, -0.15f, 0.0f);
	glScalef(0.7f, 1.5f, 0.0f);
	glTranslatef(-0.65f, 0.15f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.06f, 0.55f, 0.78f);		// azul
	glVertex3f(0.35f, 0.15f, 0.0f);	// arriba-izquierda
	glVertex3f(0.35f, -0.15f, 0.0f);	// abajo-izquierda
	glColor3f(.94f, 0.56f, 0.22f);		// naranja
	glVertex3f(0.65f, -0.15f, 0.0f);	// abajo-derecha
	glVertex3f(0.65f, 0.15f, 0.0f);	// arriba-derecha
	glEnd();
	glLoadIdentity();

	glutSwapBuffers();
	glFlush();
}


// Funcion principal
int main(int argc, char **argv)
{
	// Inicializamos la libreria GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Escena 2D con transformaciones");

	// Indicamos cuales son las funciones de redibujado y reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// El color de fondo sera blanco opaco
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

	// Comienza la ejecucion del core de GLUT
	glutMainLoop();
	return 0;
}