#include <GL/gl.h>
#include<iostream>
#include<math.h>
#include<GL/glut.h>

class screenPt
{
    	private:
		GLint x, y;
	public:
        screenPt(void)
        {
            this->x = this->y = 0;
        }

        void setCoords(GLint xCoord, GLint yCoord)
        {
            this->x = xCoord;
            this->y = yCoord;
        }

        GLint getx(void) const
        {
            return this->x;
        }

        GLint gety(void) const
        {
            return this->y;
        }

};

const double TWO_PI = 6.2831853;

GLsizei winWidth = 100, winHeight = 100;
GLuint regHex;

GLenum errorCheck(void);

void init(void)
{
	screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;

	circCtr.setCoords (winWidth , winHeight);
	glClearColor(1.0, 1.0, 1.0, 0.0);    // Set display window (White #FFFFFF)

	regHex = glGenLists(1);              // Set the identifier for the display lists
	glNewList(regHex, GL_COMPILE);       // Init new display list
	glColor3f(1.0, 0.0, 0.0);            
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		theta = TWO_PI * k / 6.0;
		hexVertex.setCoords(circCtr.getx() + 50 * cos(theta), circCtr.gety() + 50 * sin(theta));
		glVertex2i(hexVertex.getx(), hexVertex.gety());
	}
	glEnd();
	glEndList();
	glOrtho(0.0, 200.0, 0.0, 150.0, -1.0, 1.0);   // Set Orthographic window to 200 x 150 dimension window

}

void regHexagon(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(regHex);

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