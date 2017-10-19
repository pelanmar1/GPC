#include "stdafx.h"
#include <glut.h>


#define ANCHO 400
#define ALTO 400
#define ORIGENX 100
#define ORIGENY 100

void inicio(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ANCHO, 0, ALTO, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef((GLfloat)ANCHO / 2, (GLfloat)ALTO / 2, 5.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void dibujar(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3i(-100, -100, 5);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(-100, 100, 5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3i(100, 100, 5);

	glColor3f(1.0, 1.0, 0.0);
	glVertex3i(100, -100, 5);

}


int main( int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ANCHO, ALTO);
	glutInitWindowPosition(ORIGENX, ORIGENY);
	glutCreateWindow("Cuadrado Multicolor");
	inicio();
	glutDisplayFunc(dibujar);
	glutMainLoop();

    return 0;
}
