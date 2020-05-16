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
Camara cam(glm::vec3(0.0f, 0.0f, 1.0f),  // pos
	glm::vec3(0.0f, 0.0f, -1.0f),  // front
	glm::vec3(0.0f, 1.0f, 0.0f));  // up
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
//Indica el ángulo para el tilt de la cámara
GLfloat angle = 0.0f;
// Indica el tipo de proyección que se usa
int proyeccion = 0;
// Variable para proyecciones oblicuas
double alpha = -45.0;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
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
	// Activar la vista caballera o militar
	float m[16]; // identity
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	float angle = (M_PI / 180.0f) * float(alpha);
	if (proyeccion == 1) { // cavalier
		m[2 * 4 + 0] = -cos(angle);
		m[2 * 4 + 1] = sin(angle);
	}
	else if (proyeccion == 2) { // cabinet
		m[2 * 4 + 0] = -cos(angle) / 2.0f;
		m[2 * 4 + 1] = sin(angle) / 2.0f;
	}
	glMultMatrixf(m);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(posX, posY, posZ);
	glutSolidTeapot(0.1f);
	glTranslatef(-posX, -posY, -posZ);
	if (ejesVisible) referenciaEjes();
	if (planosVisible) referenciaPlanos();
	glutSwapBuffers();
	glFlush();
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
	gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z,
		cam.pos.x + cam.front.x, cam.pos.y + cam.front.y, cam.pos.z + cam.front.z,
		cam.up.x, cam.up.y, cam.up.z);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	float speed = 0.1f;
	switch (key)
	{
		// Escape
	case 27:
		exit(0);
		break;
	case 'f':
		fullscreen = !fullscreen;
		if (!fullscreen)
		{
			glutReshapeWindow(windowWidth, windowHeight);
			glutPositionWindow(50, 50);
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
		mirar(cam);
		glMatrixMode(GL_MODELVIEW);
		break;
	case 'w':
		cam.pos += speed*cam.front;
		mirar(cam);
		break;
	case 's':
		cam.pos -= speed*cam.front;
		mirar(cam);
		break;
	case 'a':
		cam.pos -= glm::normalize(glm::cross(cam.front,cam.up))*speed;
		mirar(cam);
		break;
	case 'd':
		cam.pos += glm::normalize(glm::cross(cam.front, cam.up))*speed;
		mirar(cam);
		break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	glm::vec3 prueba;
	float speed = 2.5f;
	glm::vec3 front;
	switch (key)
	{
		// alzado
	case GLUT_KEY_F1:
		proyeccion = 0;
		cam.pos=glm::vec3(0.0f, 0.0f, 1.0f);
		cam.yaw=-90.0f;
		cam.pitch=0.0f;
		cam.girar();
		mirar(cam);
		break;
		// planta
	case GLUT_KEY_F2:
		proyeccion = 0;
		cam.pos=glm::vec3(0.0f, 1.0f, 0.0f);
		cam.yaw = -90.0f;
		cam.pitch = -90.0f;
		cam.girar();
		mirar(cam);
		break;
		// perfil izquierdo
	case GLUT_KEY_F3:
		proyeccion = 0;
		cam.pos=glm::vec3(-1.0f, 0.0f, 0.0f);
		cam.yaw = 0.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// isométrica
	case GLUT_KEY_F4:
		proyeccion = 0;
		cam.pos=glm::vec3(1.0f, 0.0f, 0.0f);
		cam.yaw = 180.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// isométrica
	case GLUT_KEY_F5:
		proyeccion = 0;
		cam.pos=glm::vec3(1.0f, 1.0f, 1.0f);
		cam.yaw = -135.0f;
		cam.pitch = -glm::degrees(asin(1/sqrt(3)));
		cam.girar();
		mirar(cam);
		break;
		// caballera
	case GLUT_KEY_F6:
		profundidad = false;
		proyeccion = 1;
		cam.pos = glm::vec3(0.0f, 0.0f, 1.0f);
		cam.yaw = -90.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// militar
	case GLUT_KEY_F7:
		profundidad = false;
		proyeccion = 2;
		cam.pos = glm::vec3(0.0f, 0.0f, 1.0f);
		cam.yaw = -90.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
	case GLUT_KEY_RIGHT:
		cam.yaw += speed;
		cam.girar();
		mirar(cam);
		break;
	case GLUT_KEY_LEFT:
		cam.yaw -= speed;
		cam.girar();
		mirar(cam);
		break;
	case GLUT_KEY_UP:
		cam.pitch += speed;
		cam.girar();
		mirar(cam);
		break;
	case GLUT_KEY_DOWN:
		cam.pitch -= speed;
		cam.girar();
		mirar(cam);
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

void referenciaEjes()
{
	glPushMatrix();
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
	glPopMatrix();
}

void referenciaPlanos()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	// X / Y - Azul 30%
	glColor4f(0.0f, 0.0f, 1.0f, 0.3f);
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
	glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
	glVertex3f(0.0f, 0.9f, 0.9f);
	glVertex3f(0.0f, -0.9f, 0.9f);
	glVertex3f(0.0f, -0.9f, -0.9f);
	glVertex3f(0.0f, 0.9f, -0.9f);
	glEnd();
	glPopMatrix();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);  // El viewport cubre la ventana
	mirar(cam);
}
