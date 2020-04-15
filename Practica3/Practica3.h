#pragma once
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

const int WIDTH = 640;	// Ancho de la ventana
const int HEIGHT = 480;	// Alto de la ventana

void initGL();
void display(void);
void ejes(bool visible);
void planos(bool visible);
void reshape(int width, int height);