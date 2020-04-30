++// Practica1.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;

// Funci�n que controla la proporci�n al cambiar el tama�o
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

// Funci�n que visualiza la escena OpenGL
void display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

	// A continuaci�n dibujamos los 4 cuadrados
	// Cada grupo de 4 v�rtices es un cuadrado
	// Cuadrante arriba-izquierda
	glTranslatef(0.2f, 0.2f, 0.2f);			// Translaci�n
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);		// negro
		glVertex3f(-0.75f, 0.75f, 0.0f);	// arriba-izquierda
		glVertex3f(-0.75f, 0.25f, 0.0f);	// abajo-izquierda
		glVertex3f(-0.25f, 0.25f, 0.0f);	// abajo-derecha
		glVertex3f(-0.25f, 0.75f, 0.0f);	// arriba-derecha
	glEnd();
	glLoadIdentity();

	// Cuadrante abajo-izquierda
	glRotatef(45.0f,-0.5f,-0.5f,0.0f);		// Rotaci�n
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);		// rojo
		glVertex3f(-0.75f, -0.25f, 0.0f);	// arriba-izquierda
		glVertex3f(-0.75f, -0.75f, 0.0f);	// abajo-izquierda
		glVertex3f(-0.25f, -0.75f, 0.0f);	// abajo-derecha
		glVertex3f(-0.25f, -0.25f, 0.0f);	// arriba-derecha
	glEnd();
	glLoadIdentity();

	// Cuadrante abajo-derecha
	glScalef(1.5f, 1.5f, 0.0f);				// Escalado
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);		// verde
		glVertex3f(0.75f, -0.75f, 0.0f);	// arriba-izquierda
		glVertex3f(0.75f, -0.25f, 0.0f);	// abajo-izquierda
		glVertex3f(0.25f, -0.25f, 0.0f);	// abajo-derecha
		glVertex3f(0.25f, -0.75f, 0.0f);	// arriba-derecha
	glEnd();
	glLoadIdentity();

	// Cuadrante arriba-derecha
	GLfloat m[16] = {
		1.0f,-0.25f,0.0f,0.0f,
		0.7f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	glMultMatrixf(m);						// Cizallamiento
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 1.0f);		// azul
		glVertex3f(0.75f, 0.25f, 0.0f);		// arriba-izquierda
		glVertex3f(0.75f, 0.75f, 0.0f);		// abajo-izquierda
		glVertex3f(0.25f, 0.75f, 0.0f);		// abajo-derecha
		glVertex3f(0.25f, 0.25f, 0.0f);		// arriba-derecha
	glEnd();
	glLoadIdentity();

	glutSwapBuffers();
	glFlush();
}


// Funci�n principal
int main(int argc, char **argv)
{
	// Inicializamos la librer�a GLUT
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

	// El color de fondo ser� blanco opaco
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}