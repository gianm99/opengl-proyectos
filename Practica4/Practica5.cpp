//Practica4.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.

#include "Practica5.h"

// Indica si está en fullscreen
bool fullscreen;
// Indica si los ejes de referencia se tienen que dibujar
bool ejesVisible = true;
// Indica si los planos de referencia se tienen que dibujar
bool planosVisible = true;
bool profundidad = true;
// Indica el tipo de sombreado que se pintará
bool sombreado = true;
float deltaTime = 0.0f;	 // Tiempo entre el anterior frame y este
float lastFrame = 0.0f;  // Tiempo del frame anterior
// Representa la cámara
Camara cam(glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, -1.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
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
// Variables para la gestión de las vistas oblicuas
int proyeccion = 0;
GLfloat angle = 0.0f;
double alpha = -45.0;
// Variables para los materiales
GLfloat mspecular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat memission[] = { 0.0f,0.0f,0.0f,1.0f };
// Luces
Luz luces[5];

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
	float angle = glm::radians(float(alpha));
	if (proyeccion == 1) { // caballera
		m[2 * 4 + 0] = -cos(angle);
		m[2 * 4 + 1] = sin(angle);
	}
	else if (proyeccion == 2) { // militar
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

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);  // El viewport cubre la ventana
	mirar(cam);
}


void keyboard(unsigned char key, int x, int y)
{
	float speed = 3.0f*deltaTime;
	float pitch_rotation = 0.0f;
	glm::mat4 rotate_yaw_matrix = glm::mat4(1.f);
	glm::mat4 m = glm::mat4(1.f);  // Matriz para calculos
	glm::vec3 camFocusVector;
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
		// Dolly in
	case 'w':
		cam.pos += speed*cam.front;
		mirar(cam);
		break;
		// Dolly out
	case 's':
		cam.pos -= speed*cam.front;
		mirar(cam);
		break;
		// Travelling izquierda
	case 'a':
		cam.pos -= glm::normalize(glm::cross(cam.front, cam.up))*speed;
		mirar(cam);
		break;
		// Travelling derecha
	case 'd':
		cam.pos += glm::normalize(glm::cross(cam.front, cam.up))*speed;
		mirar(cam);
		break;
	case SPACEBAR:
		if (sombreado) {
			glShadeModel(GL_FLAT);
		}
		else {
			glShadeModel(GL_SMOOTH);
		}
		sombreado = !sombreado;
		break;
		// Plano cenital
	case '1':
		pitch_rotation = -89.999f - cam.pitch;
		cam.right = glm::normalize(glm::cross(cam.front, cam.up));
		m = glm::rotate(m, glm::radians(pitch_rotation), cam.right);
		cam.pos = glm::vec3(m*glm::vec4(-cam.front, 0.0f)) + cam.pos + cam.front;
		cam.pitch = -89.999f;
		cam.girar();
		mirar(cam);
		break;
		// Plano picado
	case '2':
		pitch_rotation = -45.0f - cam.pitch;
		cam.right = glm::normalize(glm::cross(cam.front, cam.up));
		m = glm::rotate(m, glm::radians(pitch_rotation), cam.right);
		cam.pos = glm::vec3(m*glm::vec4(-cam.front, 0.0f)) + cam.pos + cam.front;
		cam.pitch = -45.0f;
		cam.girar();
		mirar(cam);
		break;
		// Plano normal
	case '3':
		pitch_rotation = -cam.pitch;
		cam.right = glm::normalize(glm::cross(cam.front, cam.up));
		m = glm::rotate(m, glm::radians(pitch_rotation), cam.right);
		cam.pos = glm::vec3(m*glm::vec4(-cam.front, 0.0f)) + cam.pos + cam.front;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// Plano contrapicado
	case '4':
		pitch_rotation = 45.0f - cam.pitch;
		cam.right = glm::normalize(glm::cross(cam.front, cam.up));
		m = glm::rotate(m, glm::radians(pitch_rotation), cam.right);
		cam.pos = glm::vec3(m*glm::vec4(-cam.front, 0.0f)) + cam.pos + cam.front;
		cam.pitch = 45.0f;
		cam.girar();
		mirar(cam);
		break;
		// Plano nadir
	case '5':
		pitch_rotation = 89.999f - cam.pitch;
		cam.right = glm::normalize(glm::cross(cam.front, cam.up));
		m = glm::rotate(m, glm::radians(pitch_rotation), cam.right);
		cam.pos = glm::vec3(m*glm::vec4(-cam.front, 0.0f)) + cam.pos + cam.front;
		cam.pitch = 89.999f;
		cam.girar();
		mirar(cam);
		break;
	case '6':
		if (luces[1].on)
		{
			glDisable(GL_LIGHT1);
		}
		else
		{
			glEnable(GL_LIGHT1);
		}
		luces[1].on = !luces[2].on;
		break;
	case '7':
		if (luces[2].on)
		{
			glDisable(GL_LIGHT2);
		}
		else
		{
			glEnable(GL_LIGHT2);
		}
		luces[2].on = !luces[2].on;
		break;
	case '8':
		if (luces[3].on)
		{
			glDisable(GL_LIGHT3);
		}
		else
		{
			glEnable(GL_LIGHT3);
		}
		luces[3].on = !luces[3].on;
		break;
	case '9':
		if (luces[4].on)
		{
			glDisable(GL_LIGHT4);
		}
		else
		{
			glEnable(GL_LIGHT4);
		}
		luces[4].on = !luces[4].on;
		break;
	case '0':
		if (luces[0].on)
		{
			glDisable(GL_LIGHT0);
		}
		else
		{
			glEnable(GL_LIGHT0);
		}
		luces[0].on = !luces[0].on;
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
		cam.pos = glm::vec3(0.0f, 0.0f, 1.0f);
		cam.yaw = -90.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// planta
	case GLUT_KEY_F2:
		proyeccion = 0;
		cam.pos = glm::vec3(0.0f, 1.0f, 0.0f);
		cam.yaw = -90.0f;
		cam.pitch = -90.0f;
		cam.girar();
		mirar(cam);
		break;
		// perfil izquierdo
	case GLUT_KEY_F3:
		proyeccion = 0;
		cam.pos = glm::vec3(-1.0f, 0.0f, 0.0f);
		cam.yaw = 0.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// isométrica
	case GLUT_KEY_F4:
		proyeccion = 0;
		cam.pos = glm::vec3(1.0f, 0.0f, 0.0f);
		cam.yaw = 180.0f;
		cam.pitch = 0.0f;
		cam.girar();
		mirar(cam);
		break;
		// isométrica
	case GLUT_KEY_F5:
		proyeccion = 0;
		cam.pos = glm::vec3(1.0f, 1.0f, 1.0f);
		cam.yaw = -135.0f;
		cam.pitch = -glm::degrees(asin(1 / sqrt(3)));
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
	int currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentFrame - lastFrame) / 1000;
	lastFrame = currentFrame;

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

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, memission);
	configurarLuces();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
}

void configurarLuces()
{
	GLfloat position0[] = { 1.0f,1.0f,0.0f,0.0f };
	GLfloat position1[] = { 1.0f,1.0f,1.0f,0.0f };
	GLfloat position2[] = { 1.0f,1.0f,0.0f,0.0f };
	GLfloat position3[] = { 1.0f,1.0f,-1.0f,0.0f };
	GLfloat position4[] = { 1.0f,0.0f,0.0f,0.0f };
	GLfloat spot_direction0[] = { -1.0f,-1.0f,0.0f };
	GLfloat spot_direction1[] = { -1.0f,-1.0f,-1.0f,0.0f };
	GLfloat spot_direction2[] = { -1.0f,-1.0f,0.0f,0.0f };
	GLfloat spot_direction3[] = { -1.0f,-1.0f,1.0f,0.0f };
	GLfloat spot_direction4[] = { -1.0f,0.0f,0.0f,0.0f };
	GLfloat ambient[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	luces[0] = Luz((GLenum)GL_LIGHT0, position0, spot_direction0, ambient, diffuse, specular);
	luces[1] = Luz((GLenum)GL_LIGHT1, position1, spot_direction1, ambient, diffuse, specular);
	luces[2] = Luz((GLenum)GL_LIGHT2, position2, spot_direction2, ambient, diffuse, specular);
	luces[3] = Luz((GLenum)GL_LIGHT3, position3, spot_direction3, ambient, diffuse, specular);
	luces[4] = Luz((GLenum)GL_LIGHT4, position4, spot_direction4, ambient, diffuse, specular);
}