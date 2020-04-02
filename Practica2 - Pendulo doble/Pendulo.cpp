// Pendulo.cpp
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

// Función principal
int main(int argc, char **argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Creamos la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	// Se situa en el centro de la pantalla
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - W_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - W_HEIGHT) / 2);
	// Usamos doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Péndulo doble");

	// Indicamos cuales son las funciones de redibujado y reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	// El color de fondo será gris oscuro opaco
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Indicamos la velocidad a la que gira en grados
	fIncCentral = 3.0f;
	fIncInferior = 4.0f;

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}

