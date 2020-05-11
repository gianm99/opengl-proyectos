//Practica3.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include "Practica4.h"

// Indica si está en fullscreen
bool fullscreen;
// Indica si los ejes de referencia se tienen que dibujar
bool ejesVisible = true;
// Indica si los planos de referencia se tienen que dibujar
bool planosVisible = true;
// Indica si la camara debe cambiar de vista.
bool camON = false;  // HABRÍA QUE CAMBIAR ESTO

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
//Indican los parámetros de la cámara
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(posX, posY, posZ);
	glRotatef(angRot, angX, angY, angZ);
	glutSolidTeapot(0.1f);
	//glutSolidIcosahedron();
	//glColor3f(0.0f,0.0f,0.0f);
	//glutWireIcosahedron();
	if (ejesVisible)referenciaEjes();
	if (planosVisible)referenciaPlanos();
	if (camON) camaraFunc();
	glutSwapBuffers();
	glFlush();
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);  // El viewport cubre la ventana
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 10.0, 10.0);
	//gluLookAt(eyePos[0], eyePos[1], eyePos[2], refPointPos[0], refPointPos[1], refPointPos[2], vecPos[0], vecPos[1], vecPos[2]);
	glm::lookAt(cameraPos,cameraDirection,cameraUp);
	glMatrixMode(GL_MODELVIEW);
}

void camaraFunc() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, 1, 10.0, 10.0);
	//glm::lookAt();
	glm::lookAt(cameraPos, cameraDirection, cameraUp);
	camON = false;
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:  // Escape
		exit(0);
		break;

	//case 'a':
	//	camON = true;
	//	vecPos[0] += (sin(refPointPos[0])*0.05f); vecPos[1] += (sin(refPointPos[1])*0.05f); vecPos[2] += (sin(refPointPos[2])*0.05f);
	//	break;

		/*case 'd':
			camON = true;
			eyePos[0] = 0; eyePos[1] = 0; eyePos[2] = 0;
			refPointPos[0] = 0.9f; refPointPos[1] = 0; refPointPos[2] = 0;
			vecPos[0] = 0; vecPos[1] = 1; vecPos[2] = 0;
			break;

		case 'd':
			camON = true;
			eyePos[0] = 0; eyePos[1] = 0; eyePos[2] = 0;
			refPointPos[0] = 0.9f; refPointPos[1] = 0; refPointPos[2] = 0;
			vecPos[0] = 0; vecPos[1] = 1; vecPos[2] = 0;
			break;

		case 'd':
			camON = true;

			refPointPos[0] = 0.9f; refPointPos[1] = 0; refPointPos[2] = 0;
			vecPos[0] = 0; vecPos[1] = 1; vecPos[2] = 0;
			break;

		*/

	//case '1':
	//	camON = true;
	//	eyePos[0] = 0; eyePos[1] = 0; eyePos[2] = 0;
	//	refPointPos[0] = 0.9f; refPointPos[1] = 0; refPointPos[2] = 0;
	//	vecPos[0] = 0; vecPos[1] = 1; vecPos[2] = 0;
	//	break;

	//case '2':
	//	camON = true;
	//	eyePos[0] = 0; eyePos[1] = 0; eyePos[2] = 0;
	//	refPointPos[0] = 0; refPointPos[1] = 0.9f; refPointPos[2] = 0;
	//	vecPos[0] = 1; vecPos[1] = 0; vecPos[2] = 0;
	//	break;
	//case '3':
	//	camON = true;
	//	eyePos[0] = 0; eyePos[1] = 0; eyePos[2] = 0.;
	//	refPointPos[0] = 0; refPointPos[1] = 0; refPointPos[2] = 0.9f;
	//	vecPos[0] = 0; vecPos[1] = 1; vecPos[2] = 0;
	//	break;

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
		break;


	case 'p':
		planosVisible = !planosVisible;
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
	//initRandVars();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Escena 3D simple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}