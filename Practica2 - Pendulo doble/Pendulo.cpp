// Pendulo.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int W_WIDTH = 640; // Tama�o incial de la ventana
const int W_HEIGHT = 480;
GLfloat fAnguloCentral = 90.0f, fAnguloInferior = 90.0f; // �ngulos de rotaci�n de los ejes
GLfloat fIncCentral, fIncInferior;
const GLfloat MAX_ANGULO_CENTRAL = 120;
const GLfloat MAX_ANGULO_INFERIOR = 360;

void init()
{

}

// Funci�n que dibuja la escena
void display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix


	/*A continuaci�n dibujamos los rect�ngulos que representan el p�ndulo doble*/
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

	glutSwapBuffers();
	glFlush();
}

// Funci�n que permite la animaci�n de la escena
void idle(void)
{
	// Incrementamos los �ngulos
	fAnguloCentral += fIncCentral;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloCentral > MAX_ANGULO_CENTRAL || fAnguloCentral < -MAX_ANGULO_CENTRAL)
		fIncCentral = -fIncCentral;

	// Incrementamos los �ngulos
	fAnguloInferior += fIncInferior;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloInferior > MAX_ANGULO_INFERIOR)
		fAnguloInferior = 0;

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Funci�n que controla la relaci�n de aspecto
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

// Funci�n principal
int main(int argc, char **argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - W_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - W_HEIGHT) / 2);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Escena 2D con transformaciones");

	// Indicamos cuales son las funciones de redibujado y reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	// El color de fondo ser� blanco opaco
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

	// Indicamos la velocidad a la que gira
	fIncCentral = sinf(fAnguloCentral) * 2;
	fIncInferior = sinf(fAnguloInferior) * 3;
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}

