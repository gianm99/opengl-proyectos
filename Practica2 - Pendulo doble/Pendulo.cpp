// Pendulo.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int W_WIDTH = 640; // Tamaño incial de la ventana
const int W_HEIGHT = 480;
GLfloat fAnguloCentral = 90.0f,fAnguloInferior = 90.0f; // Ángulos de rotación de los ejes
GLfloat fIncCentral, fIncInferior;
const GLfloat MAX_ANGULO_CENTRAL = 120;
const GLfloat MAX_ANGULO_INFERIOR= 120;
GLfloat trayectoria[5000000];
int npuntos = 0;

// Función que controla la proporción al cambiar el tamaño
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

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

	
	/*A continuación dibujamos los rectángulos que representan el péndulo doble*/
	GLfloat aux[16];
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
	
	
	glGetFloatv(GL_MODELVIEW_MATRIX, aux);
	trayectoria[npuntos++] = aux[0];
	trayectoria[npuntos++] = aux[5];
	trayectoria[npuntos++] = aux[10];

	glBegin(GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < npuntos && npuntos>=6; i = i + 6) {
		glVertex3d(trayectoria[i], trayectoria[i+1], trayectoria[i+2]);
		glVertex3d(trayectoria[i+3], trayectoria[i+4], trayectoria[i+5]);
	}
	glEnd();
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, trayectoria);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_LINE, 0, npuntos);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void Idle(void)
{
	// Incrementamos los ángulos
	fAnguloCentral += fIncCentral;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloCentral > MAX_ANGULO_CENTRAL || fAnguloCentral < -MAX_ANGULO_CENTRAL)
		fIncCentral=-fIncCentral;

	// Incrementamos los ángulos
	fAnguloInferior+= fIncInferior;
	// Si es mayor que dos pi la decrementamos
	if (fAnguloInferior> MAX_ANGULO_CENTRAL || fAnguloInferior< -MAX_ANGULO_CENTRAL)
		fIncInferior = -fIncInferior;

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Función principal
int main(int argc, char **argv)
{
	// Inicializamos la librería GLUT
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

	// El color de fondo será blanco opaco
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

	// Indicamos la velocidad a la que gira
	fIncCentral = sinf(fAnguloCentral)*0.08;
	fIncInferior = sinf(fAnguloInferior)*0.1;
	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}