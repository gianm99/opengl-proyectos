//Practica6.cpp: Escena 3D simple
//Autores: Tomas Bordoy, Gian Lucas Martin y Jordi Sastre.
#include "Practica6.h"
bool fullscreen;
bool ejesRef = false; // Dibujar los ejes de referencia
bool planosRef = false; // Dibujar los planos de referencia
bool trazadosCaballos = false; // Dibujar la trayectoria de los caballos
bool antialiasing = true; // Usar antialiasing
bool niebla = true;
bool fillPoligonos = true; // Rellenar los polígonos
bool camCaballo = false;
enum estadoEjesPlanos { Ninguno, Ejes, Planos, Ejes_Planos }; //Estados para el dibujo de planos/referencias
estadoEjesPlanos estadoEP = Ejes; //Guarda el estado para el dibujo de planos/referencias 
bool smooth = true; // Sombreado suave
float deltaTime = 0.0f; // Tiempo entre el anterior frame y este
float lastFrame = 0.0f; // Tiempo del frame anterior
float currentFrame;
// Variables para las vistas oblicuas
Proyeccion proyeccion = normal;
GLfloat angle = 0.0f;
double alpha = -45.0;
// Variables para el movimiento
float rotacion = 0.0f;
// Cámara
Camara cam;
// Luces
Luz luces[8];
// Niebla
static GLint fogMode;
// Modelos
Model_OBJ mCaballo;
Model_OBJ mTiovivo;
Model_OBJ mEdificio;
Model_OBJ mFarola;
Model_OBJ mBanco;
Model_OBJ mTorres;
Model_OBJ mArbol1;
Model_OBJ mArbol2;
// Objetos
Objeto tiovivo;
Objeto caballos[4];
Objeto edificios[4];
Objeto farolas[4];
Objeto bancos[4];
Objeto torres;
Objeto arboles1[4];
Objeto arboles2[3];
// Ratón
float lastX = windowWidth / 2, lastY = windowHeight / 2;
boolean firstMouse = true;

#define CFRONT 0
#define CLDER  1
#define CDTR   2
#define CLIZQ  3
#define CSUP   4

#define N_TEXTURAS 5
GLuint texture_id[N_TEXTURAS];

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearStencil(0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	proyeccionOblicua(); // Activa o no la proyección oblicua
	dibujarSuelo();
	// Dibujar la trayectoria de la cámara y los objetos
	glColor3f(1.0f, 1.0f, 1.0f); // Blanco
	cam.dibujarTrayectoria();
	// Dibujar objetos del fondo
	glColor3f(0.894f, 0.615f, 0.129f);
	edificios[0].dibujar();
	glColor3f(0.937f, 0.921f, 0.501f);
	edificios[1].dibujar();
	glColor3f(0.96f, 0.57f, 0.25f);
	edificios[2].dibujar();
	glColor3f(0.588f, 0.96f, 0.25f);
	edificios[3].dibujar();
	// Dibujar objetos secundarios
	glDepthMask(GL_FALSE);
	CreaSkyBox(texture_id[CDTR]);
	glDepthMask(GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(0.3f, 0.3f, 0.3f); // Gris oscuro
	for each (Objeto farola in farolas)
	{
		farola.dibujar();
	}
	glColor3f(0.549f, 0.247f, 0.133f); // Marrón oscuro
	for each (Objeto banco in bancos)
	{
		banco.dibujar();
	}
	glColor3f(0.105f, 0.270f, 0.050f); // Verde oscuro
	for each (Objeto arbol in arboles1)
	{
		arbol.dibujar();
	}
	glColor3f(0.239f, 0.549f, 0.133f); // Verde
	for each (Objeto arbol in arboles2)
	{
		arbol.dibujar();
	}
	// Dibujar la escena
	glPushMatrix();
	glRotatef(rotacion, 0.0f, 1.0f, 0.0f);
	glColor3f(0.941f, 0.098f, 0.137f); // Rojo claro
	tiovivo.dibujar();
	glColor3f(0.901f, 0.650f, 0.560f); // Marrón claro
	for each (Objeto caballo in caballos)
	{
		caballo.dibujar();
	}
	glPopMatrix();
	for each (Objeto caballo in caballos)
	{
		caballo.dibujarTrayectoria();
	}

	referencia();
	cam.mostrarCoordenadas(windowWidth, windowHeight);

	glutSwapBuffers();
}

void idle(void)
{
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentFrame - lastFrame) / 1000;
	lastFrame = currentFrame;

	// Guardar trayectorias
	cam.guardarTrayectoria();
	caballos[0].guardarTrayectoria(rotacion - 90.0f);
	caballos[1].guardarTrayectoria(rotacion);
	caballos[2].guardarTrayectoria(rotacion + 90.0f);
	caballos[3].guardarTrayectoria(rotacion + 180.0f);
	// Rotación
	rotacion -= 45.0f * deltaTime;
	if (rotacion < -360.0f)
	{
		rotacion = -(int)rotacion % 360;
	}
	// Movimiento de los caballos
	for (int i = 0; i < 4; i++)
	{
		caballos[i].pos.y += caballos[i].vel.y*deltaTime;
		if (caballos[i].pos.y > horseMax)
		{
			caballos[i].pos.y = horseMax;
			caballos[i].cambiarDireccion();
		}
		else if (caballos[i].pos.y < horseMin)
		{
			caballos[i].pos.y = horseMin;
			caballos[i].cambiarDireccion();
		}
	}
	// Cámara subjetiva a un caballo
	if (camCaballo) {
		cam.pos.y = caballos[1].pos.y + 1.25f;
		cam.pos.x = -3.35739994*cos(glm::radians(rotacion));
		cam.pos.z = 3.35739994*sin(glm::radians(rotacion));
		cam.mirar();
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
		switch (estadoEP) {
		case Ninguno:
			ejesRef = false;
			planosRef = false;
			estadoEP = Ejes;
			break;
		case Ejes:
			ejesRef = true;
			estadoEP = Planos;
			break;
		case Planos:
			ejesRef = false;
			planosRef = true;
			estadoEP = Ejes_Planos;
			break;
		case Ejes_Planos:
			ejesRef = true;
			estadoEP = Ninguno;
			break;
		}
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
	case 't':
		trazadosCaballos = !trazadosCaballos;
		for (int i = 0; i < 4; i++)
		{
			caballos[i].setTrayectoriaVisible(trazadosCaballos);
		}
		break;
	case 'b':
		fillPoligonos = !fillPoligonos;
		if (fillPoligonos)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		break;
	case 'm':
		antialiasing = !antialiasing;
		if (antialiasing)
		{
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
		}
		else
		{
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
		}
		break;
	case 'n':
		if (niebla) {
			if (fogMode == GL_EXP) {
				fogMode = GL_EXP2;
			}
			else if (fogMode == GL_EXP2) {
				fogMode = GL_LINEAR;
			}
			else if (fogMode == GL_LINEAR) {
				fogMode = GL_EXP;
				niebla = !niebla;
				glDisable(GL_FOG);
			}
		}
		else {
			glEnable(GL_FOG);
			niebla = !niebla;
		}
		glFogi(GL_FOG_MODE, fogMode);
		glutPostRedisplay();
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
	case 'v':
		camCaballo = !camCaballo;
		break;
	case '0':
		luces[4].alternar();
		luces[5].alternar();
		luces[6].alternar();
		luces[7].alternar();
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
	}
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
		glVertex3f(-15.0f, 0.0f, 0.0f);
		glVertex3f(15.0f, 0.0f, 0.0f);
		// Y
		glColor3f(0.0f, 1.0f, 0.0f); // Verde
		glVertex3f(0.0f, -15.0f, 0.0f);
		glVertex3f(0.0f, 15.0f, 0.0f);
		// Z
		glColor3f(0.0f, 0.0f, 1.0f); // Azul
		glVertex3f(0.0f, 0.0f, -15.0f);
		glVertex3f(0.0f, 0.0f, 15.0f);
		glEnd();
	}
	if (planosRef)
	{
		glBegin(GL_QUADS);
		// X / Y - Azul 30%
		glColor4f(0.0f, 0.0f, 1.0f, 0.3f);
		glVertex3f(15.0f, 15.0f, 0.0f);
		glVertex3f(-15.0f, 15.0f, 0.0f);
		glVertex3f(-15.0f, -15.0f, 0.0f);
		glVertex3f(15.0f, -15.0f, 0.0f);
		// X / Z - Verde 30%
		glColor4f(0.0f, 1.0f, 0.0f, 0.3f);
		glVertex3f(15.0f, 0.0f, 15.0f);
		glVertex3f(-15.0f, 0.0f, 15.0f);
		glVertex3f(-15.0f, 0.0f, -15.0f);
		glVertex3f(15.0f, 0.0f, -15.0f);
		// Y / Z - Azul 30%
		glColor4f(1.0f, 0.0f, 0.0f, 0.3f);
		glVertex3f(0.0f, 15.0f, 15.0f);
		glVertex3f(0.0f, -15.0f, 15.0f);
		glVertex3f(0.0f, -15.0f, -15.0f);
		glVertex3f(0.0f, 15.0f, -15.0f);
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
	GLfloat position0[] = { 0.0f, 50.0f, 0.0f, 0.0f };
	GLfloat position1[] = { -70.0, 20.0f, 0.0f, 0.0f };
	GLfloat position2[] = { 50.0f, 50.0f, 0.0f, 0.0f };
	GLfloat position3[] = { 50.0f, 50.0f, 50.0f, 0.0f };
	GLfloat position4[] = { 8.36f, 5.92f, -3.63f, 1.0f };
	GLfloat position5[] = { 3.64f, 5.92f, 8.36f, 1.0f };
	GLfloat position6[] = { -8.36f, 5.92f, 3.63f, 1.0f };
	GLfloat position7[] = { -3.64f, 5.92f, -8.36f, 1.0f };
	GLfloat spot_direction0[] = { 0.0f, 0.0f, 0.0f };
	GLfloat spot_direction1[] = { 0.0f, 0.0f, 0.0f };
	GLfloat spot_direction2[] = { 0.0f, 0.0f, 0.0f };
	GLfloat spot_direction3[] = { 0.0f, 0.0f, 0.0f };
	GLfloat spot_direction4567[] = { 0.0f, -1.0f, 0.0f };
	GLfloat cut1 = 180;
	GLfloat cut2 = 52;
	luces[0] = Luz((GLenum)GL_LIGHT0, position0, spot_direction0, &cut1, true);
	luces[1] = Luz((GLenum)GL_LIGHT1, position1, spot_direction1, &cut1, false);
	luces[2] = Luz((GLenum)GL_LIGHT2, position2, spot_direction2, &cut1, false);
	luces[3] = Luz((GLenum)GL_LIGHT3, position3, spot_direction3, &cut1, false);
	luces[4] = Luz((GLenum)GL_LIGHT4, position4, spot_direction4567, &cut2, false);
	luces[5] = Luz((GLenum)GL_LIGHT5, position5, spot_direction4567, &cut2, false);
	luces[6] = Luz((GLenum)GL_LIGHT6, position6, spot_direction4567, &cut2, false);
	luces[7] = Luz((GLenum)GL_LIGHT7, position7, spot_direction4567, &cut2, false);
}

void initObjetos()
{
	// Cargar los modelos
	mCaballo.Load("Modelos/Caballo.obj");
	mTiovivo.Load("Modelos/Tiovivo.obj");
	mEdificio.Load("Modelos/Edificio.obj");
	mFarola.Load("Modelos/Farola.obj");
	mBanco.Load("Modelos/Banco.obj");
	mArbol1.Load("Modelos/Arbol1.obj");
	mArbol2.Load("Modelos/Arbol2.obj");
	// Posicionar los objetos en la escena
	// Objetos de la escena
	tiovivo = Objeto(mTiovivo, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	caballos[0] = Objeto(mCaballo, glm::vec3(3.3574f, 2.23712f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	caballos[1] = Objeto(mCaballo, glm::vec3(0.0f, 2.55784f, -3.3574f), glm::vec3(0.0f, 90.0f, 0.0f));
	caballos[2] = Objeto(mCaballo, glm::vec3(-3.3574f, 3.10403f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f));
	caballos[3] = Objeto(mCaballo, glm::vec3(0.0f, 2.78831f, 3.3574f), glm::vec3(0.0f, -90.0f, 0.0f));
	for (int i = 0; i < 4; i++)
	{
		caballos[i].vel = glm::vec3(0.0f, 0.866f, 0.0f);
	}
	// Objetos secundarios
	arboles1[0] = Objeto(mArbol1, glm::vec3(-13.586f, 0.0f, 13.5265f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles1[1] = Objeto(mArbol1, glm::vec3(-10.0f, 0.0f, -12.8954f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles1[2] = Objeto(mArbol1, glm::vec3(10.0f, 0.0f, -18.1351f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles1[3] = Objeto(mArbol1, glm::vec3(15.9371f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles2[0] = Objeto(mArbol2, glm::vec3(14.8497f, 0.0f, -2.28204f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles2[1] = Objeto(mArbol2, glm::vec3(4.08433f, 0.0f, 16.8323f), glm::vec3(0.0f, 0.0f, 0.0f));
	arboles2[2] = Objeto(mArbol2, glm::vec3(-14.9429f, 0.0f, -3.55794f), glm::vec3(0.0f, 0.0f, 0.0f));
	// Objetos de fondo
	edificios[0] = Objeto(mEdificio, glm::vec3(-42.3058f, 0.0f, 31.0456f), glm::vec3(0.0f, -45.0f, 0.0f));
	edificios[1] = Objeto(mEdificio, glm::vec3(-36.1186f, 0.0f, -40.4119f), glm::vec3(0.0f, -135.0f, 0.0f));
	edificios[2] = Objeto(mEdificio, glm::vec3(42.5663f, 0.0f, -30.0f), glm::vec3(0.0f, -225.0f, 0.0f));
	edificios[3] = Objeto(mEdificio, glm::vec3(34.2859f, 0.0f, 42.8227f), glm::vec3(0.0f, 45.0f, 0.0f));
	farolas[0] = Objeto(mFarola, glm::vec3(3.63164f, 0.0f, 10.0f), glm::vec3(0.0f, -90.0f, 0.0f));
	farolas[1] = Objeto(mFarola, glm::vec3(-10.0f, 0.0f, 3.63164f), glm::vec3(0.0f, 180.0f, 0.0f));
	farolas[2] = Objeto(mFarola, glm::vec3(-3.63164f, 0.0f, -10.0f), glm::vec3(0.0f, 90.0f, 0.0f));
	farolas[3] = Objeto(mFarola, glm::vec3(10.0f, 0.0f, -3.63164f), glm::vec3(0.0f, 0.0f, 0.0f));
	bancos[0] = Objeto(mBanco, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	bancos[1] = Objeto(mBanco, glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f));
	bancos[2] = Objeto(mBanco, glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 180.0f, 0.0f));
	bancos[3] = Objeto(mBanco, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f));
}

void dibujarSuelo() {
	int GridSizeX = 80;
	int GridSizeZ = 80;
	float SizeX = 2.5f;
	float SizeZ = 2.5f;
	glBegin(GL_QUADS);


	for (int x = -(GridSizeX / 2); x < (GridSizeX / 2); ++x)
		for (int z = -(GridSizeZ / 2); z < (GridSizeZ / 2); ++z)
		{
			if (((x + z) % 2) == 0) //modulo 2
				glColor3f(1.0f, 1.0f, 1.0f); //white
			else
				glColor3f(0.0f, 0.0f, 0.0f); //black

			glVertex3f(x*SizeX, 0, z*SizeZ);
			glVertex3f((x + 1)*SizeX, 0, z*SizeZ);
			glVertex3f((x + 1)*SizeX, 0, (z + 1)*SizeZ);
			glVertex3f(x*SizeX, 0, (z + 1)*SizeZ);

		}
	glEnd();
}


void CreaSkyBox(GLuint n_de_textura)
{
	// Desenha Cubo 1
	glColor3f(1.0f, 1.0f, 1.0f);
	// define qual das texturas usar
	glBindTexture(GL_TEXTURE_2D, n_de_textura);

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -10.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -10.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, -10.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100.0f, -10.0f, -100.0f);

	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, -10.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, -10.0f, -100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100.0f, -10.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, -10.0f, 100.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -10.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100.0f, -10.0f, 100.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -10.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, -10.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 100.0f, -100.0f);
	glEnd();


}


void camaraRaton(int posx, int posy) {
	if (firstMouse)
	{
		lastX = posx;
		lastY = posy;
		firstMouse = false;
	}

	float xoffset = posx - lastX;
	float yoffset = lastY - posy;
	lastX = posx;
	lastY = posy;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	cam.yaw += xoffset;
	cam.pitch += yoffset;

	if (cam.pitch > 89.0f)
		cam.pitch = 89.0f;
	if (cam.pitch < -89.0f)
		cam.pitch = -89.0f;


	if (posx < 100 || posx > windowWidth - 200) {
		lastX = windowWidth / 2;
		lastY = windowHeight / 2;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	else if (posy < 100 || posy > windowHeight - 200) {
		lastX = windowWidth / 2;
		lastY = windowHeight / 2;
		glutWarpPointer(windowWidth / 2, windowHeight / 2);
	}
	cam.mirar();
}

void init()
{
	GLfloat mspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat memission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat globalAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };

	glClearColor(0.0f, 0.67f, 0.79f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_STENCIL_TEST);
	//Ratón
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(camaraRaton);
	// Iluminación
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, memission);
	glLightModelfv(GL_AMBIENT, globalAmbient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	initLuces();
	// Niebla
	glEnable(GL_FOG);
	{
		GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

		fogMode = GL_EXP;
		glFogi(GL_FOG_MODE, fogMode);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.05);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 15.0);
		glFogf(GL_FOG_END, 30.0);
	}
	//glClearColor(0.5, 0.5, 0.5, 1.0);  /* fog color */
	// Cámara
	cam = Camara(glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	cam.vista(isometrica);
	cam.mirar();
	// Objetos
	initObjetos();
	// Callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
}

void initTexture()
{

	image_t temp_image; // variável que irá armazenar a textura a ser usada

						// Habilita o uso de textura 
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Define quantas texturas serão usadas no programa 
	glGenTextures(1, texture_id);  // 1 = uma textura;
								   // texture_id = vetor que guardas os números das texturas

								   // Define os números da textura dos cubos
								   //Paredes y techo. 
	texture_id[CFRONT] = 1001;
	texture_id[CLDER] = 1002;
	texture_id[CDTR] = 1003;
	texture_id[CLIZQ] = 1004;
	texture_id[CSUP] = 1005;



	glBindTexture(GL_TEXTURE_2D, texture_id[CFRONT]);
	tgaLoad("texturas/zpos.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CLDER]);
	tgaLoad("texturas/xpos.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CDTR]);
	tgaLoad("texturas/zneg.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CLIZQ]);
	tgaLoad("texturas/xneg.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CSUP]);
	tgaLoad("texturas/ypos.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);


}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Tiovivo");
	init();
	initTexture();
	glutMainLoop();
	return 0;
}

