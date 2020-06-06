//Practica6.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.
#include "Practica6.h"

bool fullscreen;
bool ejesRef = true; // Dibujar los ejes de referencia
bool planosRef = true; // Dibujar los planos de referencia
bool smooth = true; // Sombreado suave
float deltaTime = 0.0f; // Tiempo entre el anterior frame y este
float lastFrame = 0.0f; // Tiempo del frame anterior
// Variables para las vistas oblicuas
Proyeccion proyeccion = normal;
GLfloat angle = 0.0f;
double alpha = -45.0;
// Variables para el movimiento
float rotacion = 0.0f;
// Cámara
Camara cam;
// Luces
Luz luces[4];
// Objetos
Objeto tiovivo;
Objeto caballos[4];
// Modelos
Model_OBJ modeloCaballo;
Model_OBJ modeloTiovivo;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	proyeccionOblicua(); // Activa o no la proyección oblicua
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(rotacion, 0.0f, 1.0f, 0.0f);
	tiovivo.dibujar();
	for each (Objeto caballo in caballos)
	{
		caballo.dibujar();
	}
	cam.dibujarTrayectoria();
	glPopMatrix();
	referencia();
	glutSwapBuffers();
	glFlush();
}

void idle(void)
{
	int currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentFrame - lastFrame) / 1000;
	lastFrame = currentFrame;

	// Guardar trayectorias
	cam.guardarTrayectoria();
	for each (Objeto caballo in caballos)
	{
		caballo.guardarTrayectoria();
	}

	// Rotación
	rotacion -= 45.0f * deltaTime;
	if (rotacion < -360.0f)
	{
		rotacion = 0;
	}
	// Movimiento de los caballos
	for (int i=0; i<4;i++)
	{
		caballos[i].pos.y+=caballos[i].vel.y*deltaTime;
		if (caballos[i].pos.y>3.10403f)
		{
			caballos[i].pos.y= 3.10403f;
			caballos[i].cambiarDireccion();
		}
		else if (caballos[i].pos.y < 2.23712f)
		{
			caballos[i].pos.y= 2.23712f;
			caballos[i].cambiarDireccion();
		}
	}
	glutPostRedisplay();
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height); // El viewport cubre la ventana
}

void keyboard(unsigned char key, int x, int y)
{
	float speed = 10.0f * deltaTime;
	glm::vec3 position;
	switch (key)
	{
	case KEY_ESCAPE:
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
		ejesRef = !ejesRef;
		planosRef = !planosRef;
		break;
	case 'p':
		cam.cambiarProfundidad();
		cam.mirar();
		break;
		// Dolly in
	case 'w':
		cam.pos += speed * cam.front;
		cam.mirar();
		break;
		// Dolly out
	case 's':
		cam.pos -= speed * cam.front;
		cam.mirar();
		break;
		// Travelling izquierda
	case 'a':
		cam.pos -= glm::normalize(glm::cross(cam.front, cam.up)) * speed;
		cam.mirar();
		break;
		// Travelling derecha
	case 'd':
		cam.pos += glm::normalize(glm::cross(cam.front, cam.up)) * speed;
		cam.mirar();
		break;
	case KEY_SPACE:
		smooth = !smooth;
		if (smooth)
		{
			glShadeModel(GL_SMOOTH);
		}
		else
		{
			glShadeModel(GL_FLAT);
		}
		break;
	case '1':
		cam.orbital(cenital);
		cam.mirar();
		break;
	case '2':
		cam.orbital(picado);
		cam.mirar();
		break;
	case '3':
		cam.orbital(base);
		cam.mirar();
		break;
	case '4':
		cam.orbital(contrapicado);
		cam.mirar();
		break;
	case '5':
		cam.orbital(nadir);
		cam.mirar();
		break;
		// Luz 0
	case '6':
		luces[0].alternar();
		break;
		// Luz 1
	case '7':
		luces[1].alternar();
		break;
		// Luz 2
	case '8':
		luces[2].alternar();
		break;
		// Luz 3
	case '9':
		luces[3].alternar();
		break;
		// Mover luz 0 a posición 1
	case 'z':
		luces[0].mover(glm::vec3{ -1.0f,0.0f,1.0f });
		break;
		// Mover luz 0 a posición 2
	case 'x':
		luces[0].mover(glm::vec3{ -1.0f,1.0f,1.0f });
		break;
		// Mover luz 0 a posición 3
	case 'c':
		luces[0].mover(glm::vec3{ -1.0f ,1.0f,0.0f });
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
		proyeccion = normal;
		cam.vista(alzado);
		break;
		// planta
	case GLUT_KEY_F2:
		proyeccion = normal;
		cam.vista(planta);
		break;
		// perfil izquierdo
	case GLUT_KEY_F3:
		proyeccion = normal;
		cam.vista(p_izquierdo);
		break;
		// perfil derecho
	case GLUT_KEY_F4:
		proyeccion = normal;
		cam.vista(p_derecho);
		break;
		// isométrica
	case GLUT_KEY_F5:
		proyeccion = normal;
		cam.vista(isometrica);
		break;
		// caballera
	case GLUT_KEY_F6:
		cam.ortogonal();
		proyeccion = caballera;
		cam.vista(alzado);
		break;
		// militar
	case GLUT_KEY_F7:
		cam.ortogonal();
		proyeccion = militar;
		cam.vista(alzado);
		break;
		// yaw derecha
	case GLUT_KEY_RIGHT:
		cam.yaw += speed;
		cam.mirar();
		break;
		// yaw izquierda
	case GLUT_KEY_LEFT:
		cam.yaw -= speed;
		cam.mirar();
		break;
		// pitch arriba
	case GLUT_KEY_UP:
		cam.pitch += speed;
		cam.mirar();
		break;
		// pitch abajo
	case GLUT_KEY_DOWN:
		cam.pitch -= speed;
		cam.mirar();
		break;
	}
}

void referencia()
{
	glPushMatrix();
	if (ejesRef)
	{
		glBegin(GL_LINES);
		// X
		glColor3f(1.0f, 0.0f, 0.0f); // Rojo
		glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(10.0f, 0.0f, 0.0f);
		// Y
		glColor3f(0.0f, 1.0f, 0.0f); // Verde
		glVertex3f(0.0f, -10.0f, 0.0f);
		glVertex3f(0.0f, 10.0f, 0.0f);
		// Z
		glColor3f(0.0f, 0.0f, 1.0f); // Azul
		glVertex3f(0.0f, 0.0f, -10.0f);
		glVertex3f(0.0f, 0.0f, 10.0f);
		glEnd();
	}
	if (planosRef)
	{
		glBegin(GL_QUADS);
		// X / Y - Azul 30%
		glColor4f(0.0f, 0.0f, 1.0f, 0.3f);
		glVertex3f(9.0f, 9.0f, 0.0f);
		glVertex3f(-9.0f, 9.0f, 0.0f);
		glVertex3f(-9.0f, -9.0f, 0.0f);
		glVertex3f(9.0f, -9.0f, 0.0f);
		// X / Z - Verde 30%
		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glVertex3f(9.0f, 0.0f, 9.0f);
		glVertex3f(-9.0f, 0.0f, 9.0f);
		glVertex3f(-9.0f, 0.0f, -9.0f);
		glVertex3f(9.0f, 0.0f, -9.0f);
		// Y / Z - Azul 30%
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glVertex3f(0.0f, 9.0f, 9.0f);
		glVertex3f(0.0f, -9.0f, 9.0f);
		glVertex3f(0.0f, -9.0f, -9.0f);
		glVertex3f(0.0f, 9.0f, -9.0f);
		glEnd();
	}
	glPopMatrix();
}

void proyeccionOblicua()
{
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	float angle = glm::radians(float(alpha));
	switch (proyeccion)
	{
	case caballera:
		m[2 * 4 + 0] = -cos(angle);
		m[2 * 4 + 1] = sin(angle);
		break;
	case militar:
		m[2 * 4 + 0] = -cos(angle) / 2.0f;
		m[2 * 4 + 1] = sin(angle) / 2.0f;
		break;
	}
	glMultMatrixf(m);
}

void initLuces()
{
	GLfloat position0[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	GLfloat position1[] = { 10.0f, 10.0f, 0.0f, 1.0f };
	GLfloat position2[] = { 10.0f, 10.0f, -10.0f, 1.0f };
	GLfloat position3[] = { 10.0f, 0.0f, 0.0f, 1.0f };
	GLfloat spot_direction0[] = { -10.0f, -10.0f, -10.0f };
	GLfloat spot_direction1[] = { -10.0f, -10.0f, 0.0f };
	GLfloat spot_direction2[] = { -10.0f, -10.0f, 10.0f };
	GLfloat spot_direction3[] = { -10.0f, 0.0f, 0.0f };
	luces[0] = Luz((GLenum)GL_LIGHT0, position0, spot_direction0, false);
	luces[1] = Luz((GLenum)GL_LIGHT1, position1, spot_direction1, true);
	luces[2] = Luz((GLenum)GL_LIGHT2, position2, spot_direction2, false);
	luces[3] = Luz((GLenum)GL_LIGHT3, position3, spot_direction3, false);
}

void initObjetos()
{
	tiovivo = Objeto(modeloTiovivo, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), false);
	caballos[0] = Objeto(modeloCaballo, glm::vec3(3.3574f, 2.23712f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), true);
	caballos[1] = Objeto(modeloCaballo, glm::vec3(0.0f, 2.55784f, -3.3574f), glm::vec3(0.0f, 90.0f, 0.0f), true);
	caballos[2] = Objeto(modeloCaballo, glm::vec3(-3.3574f, 3.10403f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f), true);
	caballos[3] = Objeto(modeloCaballo, glm::vec3(0.0f, 2.78831f, 3.3574f), glm::vec3(0.0f, -90.0f, 0.0f), true);
	for (int i = 0; i<4; i++)
	{
		caballos[i].vel = glm::vec3(0.0f, 0.866f, 0.0f);
	}
}

void init()
{
	GLfloat mspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat memission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat globalAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Iluminación
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, memission);
	glLightModelfv(GL_AMBIENT, globalAmbient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	initLuces();
	// Cámara
	cam = Camara(glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	cam.mirar();
	// Objetos
	modeloCaballo.Load("Modelos/arabian.obj");
	modeloTiovivo.Load("Modelos/Tiovivo.obj");
	initObjetos();
	// Callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Tiovivo");
	init();
	glutMainLoop();
	return 0;
}