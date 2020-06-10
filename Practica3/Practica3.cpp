//Practica3.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include "Practica3.h"

// Indica si está en modo fullscreen
bool fullscreen;
// Indica si los ejes de referencia se tienen que dibujar
bool ejesRef=true;
// Indica si los planos de referencia se tienen que dibujar
bool planosRef=true;
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
// Objetos
Objeto Tet(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0050f));
Objeto Esf(glm::vec3(0.6f, 0.6f, 0.0f), glm::vec3(0.005f, 0.0f, 0.0f));
Objeto Cub(glm::vec3(-0.6f, -0.6f, 0.0f), glm::vec3(0.0f, 0.005f, 0.0f));
//Indican el tamaño inicial de la ventana
GLsizei windowWidth = 640;
GLsizei windowHeight = 640;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	trazadoElem(Tet.posiciones);
	trazadoElem(Esf.posiciones);
	trazadoElem(Cub.posiciones);
	dibujarTetera();
	dibujarEsfera();
	dibujarCubo();
	if (ejesRef) referenciaEjes();
	if (planosRef) referenciaPlanos();
	glutSwapBuffers();
	glFlush();
}

void dibujarTetera() {

	glLoadIdentity();
	glPushMatrix();

	glTranslatef(Tet.pos.x, Tet.pos.y, Tet.pos.z);
	glutSolidTeapot(0.1f);
	glTranslatef(-Tet.pos.x, -Tet.pos.y, -Tet.pos.z);

	glPopMatrix();
}

void dibujarEsfera() {

	glLoadIdentity();
	glPushMatrix();

	glTranslatef(Esf.pos.x, Esf.pos.y, Esf.pos.z);
	glutSolidSphere(0.1f, 100, 100);
	glTranslatef(-Esf.pos.x, -Esf.pos.y, -Esf.pos.z);

	glPopMatrix();
}

void dibujarCubo() {

	glLoadIdentity();
	glPushMatrix();

	glTranslatef(Cub.pos.x, Cub.pos.y, Cub.pos.z);
	glutSolidCube(0.1);
	glTranslatef(-Cub.pos.x, -Cub.pos.y, -Cub.pos.z);

	glPopMatrix();

}

void reshape(GLsizei width, GLsizei height)
{
	// Calcular el aspect ratio de la nueva ventana
	if (height == 0) height = 1;  // Para evitar dividir por cero
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Hacer que el viewport cubra la nueva ventana
	glViewport(0, 0, width, height);
	// Hacer que el aspect ratio del área de dibujado sea igual al del viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		glFrustum(1.0 * aspect, 1.0 * aspect, 1.0, 1.0, 2.0, 2.0);
	}
	else {
		glFrustum(1.0, 1.0, 1.0 / aspect, 1.0 / aspect, 2.0, 2.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:  // Escape
			exit(0);
			break;
		case 'f':
			fullscreen=!fullscreen;
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
			ejesRef=!ejesRef;
			break;
		case 'p':
			planosRef=!planosRef;
			break;
	}
}

void idle(void) {

	// Guardar posiciones de objetos
	if (Tet.posiciones.size() == 50)
	{
		Tet.posiciones.pop_front();
	}
	Tet.posiciones.push_back(Tet.pos);
	if (Esf.posiciones.size() == 50) {
		Esf.posiciones.pop_front();
	}
	Esf.posiciones.push_back(Esf.pos);
	if (Cub.posiciones.size() == 50) {
		Cub.posiciones.pop_front();
	}
	Cub.posiciones.push_back(Cub.pos);


	//tetera
	if (Tet.pos.z > 0.7f || Tet.pos.z < -0.7f)
	{
		Tet.inc.z = -Tet.inc.z;
	}
	if (Tet.pos.x > 0.7f || Tet.pos.x < -0.7f) {
		Tet.inc.x = -Tet.inc.x;
	}
	if (Tet.pos.y > 0.7f || Tet.pos.y < -0.7f) {
		Tet.inc.y = -Tet.inc.y;
	}
	Tet.pos.x += Tet.inc.x;
	Tet.pos.y += Tet.inc.y;
	Tet.pos.z += Tet.inc.z;

	//esfera
	if (Esf.pos.z > 0.7f || Esf.pos.z < -0.7f)
	{
		Esf.inc.z = -Esf.inc.z;
	}
	if (Esf.pos.x > 0.7f || Esf.pos.x < -0.7f) {
		Esf.inc.x = -Esf.inc.x;
	}
	if (Esf.pos.y > 0.7f || Esf.pos.y < -0.7f) {
		Esf.inc.y = -Esf.inc.y;
	}
	Esf.pos.x += Esf.inc.x;
	Esf.pos.y += Esf.inc.y;
	Esf.pos.z += Esf.inc.z;

	//cubo

	if (Cub.pos.z > 0.7f || Cub.pos.z < -0.7f)
	{
		Cub.inc.z = -Cub.inc.z;
	}
	if (Cub.pos.x > 0.7f || Cub.pos.x < -0.7f) {
		Cub.inc.x = -Cub.inc.x;
	}
	if (Cub.pos.y > 0.7f || Cub.pos.y < -0.7f) {
		Cub.inc.y = -Cub.inc.y;
	}
	Cub.pos.x += Cub.inc.x;
	Cub.pos.y += Cub.inc.y;
	Cub.pos.z += Cub.inc.z;

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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("Escena 3D simple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void trazadoElem(std::deque <glm::vec3> pos) {
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pos.size(); i++)
	{
		glVertex3f(pos[i].x, pos[i].y, pos[i].z);
	}
	glEnd();
	glPopMatrix();
}
