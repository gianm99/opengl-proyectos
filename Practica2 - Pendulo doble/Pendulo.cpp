// Pendulo.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int W_WIDTH = 640; // Tama�o incial de la ventana
const int W_HEIGHT = 480;
GLfloat fAnguloCentral,fAnguloInferior; // �ngulos de rotaci�n de los ejes
GLfloat fIncCentral, fIncInferior;
const GLfloat MAX_ANGULO_CENTRAL = 120;
const GLfloat MAX_ANGULO_INFERIOR= 120;

// Funci�n que controla la proporci�n al cambiar el tama�o
void Reshape(int width, int height)
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
void Display(void)
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
	glColor3f(0.89f, 0.15f, 0.21f);		// rojo
	glVertex3f(-0.01f, 0.0f, 0.0f);	// SUPERIOR IZQUIERDA
	glVertex3f(-0.01f, -0.5f, 0.0f);	// INFERIOR IZQUIERDA
	glVertex3f(0.01f, -0.5f, 0.0f);	// INFERIOR DERECHA
	glVertex3f(0.01f, 0.0f, 0.0f);	// SUPERIOR DERECHA
	glEnd();

	// Parte inferior
	//glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(fAnguloInferior, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(0.89f, 0.15f, 0.21f);		// rojo
	glVertex3f(-0.01f, -0.5f, 0.0f);	// SUPERIOR IZQUIERDA
	glVertex3f(-0.01f, -0.95f, 0.0f);	// INFERIOR IZQUIERDA
	glVertex3f(0.01f, -0.95f, 0.0f);	// INFERIOR DERECHA
	glVertex3f(0.01f, -0.5f, 0.0f);	// SUPERIOR DERECHA
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void Idle(void)
{
	// Incrementamos los �ngulos
	fAnguloCentral += fIncCentral;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloCentral > MAX_ANGULO_CENTRAL || fAnguloCentral < -MAX_ANGULO_CENTRAL)
		fIncCentral=-fIncCentral;

	// Incrementamos los �ngulos
	fAnguloInferior+= fIncInferior;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloInferior> MAX_ANGULO_CENTRAL || fAnguloInferior< -MAX_ANGULO_CENTRAL)
		fIncInferior = -fIncInferior;

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Funci�n principal
int main(int argc, char **argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Escena 2D con transformaciones");

	// Indicamos cuales son las funciones de redibujado y reshape
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);

	// El color de fondo ser� blanco opaco
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

	// Indicamos la velocidad a la que gira
	fIncCentral = 0.2f;
	fIncInferior = 0.25f;
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}