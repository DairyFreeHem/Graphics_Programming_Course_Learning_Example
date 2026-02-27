#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstdlib>
#include<GL/glut.h>

#include "screenPt.h"

const double TWO_PI = 6.2831853;

GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

GLenum errorCheck(void);

void init(void)
{
	screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;

	circCtr.setCoords (winWidth, winHeight);
	glClearColor(1.0, 1.0, 1.0, 0.0);    // Set display window (White #FFFFFF)

	regHex = glGenLists(1);              // Set the identifier for the display lists
	glNewList(regHex, GL_COMPILE);       // Init new display list
	glColor3f(1.0, 0.0, 0.0);            
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		theta = TWO_PI * k / 6.0;
		hexVertex.setCoords(circCtr.getx() + 150 * cos(theta), circCtr.gety() + 150 * sin(theta));
		glVertex2i(hexVertex.getx(), hexVertex.gety());
	}
	glEnd();
	glEndList();
}

void regHexagon(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(regHex);

	glFlush();
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_LINES);
	glVertex2i(180, 15);
	glVertex2i(10, 145);
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Salut, tout le monde! ");
	errorCheck();

	init();
	errorCheck();
	glutDisplayFunc(regHexagon);
	errorCheck();
	glutMainLoop();

	return 0;
}


GLenum errorCheck(void)
{
	GLenum code;
	const GLubyte* errStr;

	code = glGetError();
	if (code != GL_NO_ERROR)
	{
		errStr = gluErrorString(code);
		std::cerr << "OpenGL error: " << errStr;
	}
	return code;
}