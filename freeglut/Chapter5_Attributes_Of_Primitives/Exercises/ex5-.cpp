// Didn't understand assignment, got confused

#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstdlib>
#include<GL/glut.h>

const double TWO_PI = 6.2831853;

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


GLsizei winWidth = 100, winHeight = 80;
GLuint regHex;

GLenum errorCheck(void);

void init(void)
{


	glClearColor(1.0, 1.0, 1.0, 0.0);    // Set display window (White #FFFFFF)

    
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window

	glEndList();
}

void regHexagon(void)
{
    screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;

    circCtr.setCoords (winWidth, winHeight);

	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.3, 0.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
		for (k = 0; k < 360; k++)
		{
			theta = k ;
			hexVertex.setCoords(circCtr.getx() + 60 * cos(theta), circCtr.gety() + 60 * sin(theta));
			glVertex2i(hexVertex.getx(), hexVertex.gety());
		}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		for (k = 0; k < 360; k++)
		{
			theta = k ;
			hexVertex.setCoords(circCtr.getx() + 50 * cos(theta), circCtr.gety() + 50 * sin(theta));
			glVertex2i(hexVertex.getx(), hexVertex.gety());
		}
	glEnd();

	glColor3f(0.6, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
		for (k = 0; k < 360; k++)
		{
			theta = k ;
			hexVertex.setCoords(circCtr.getx() + 40 * cos(theta), circCtr.gety() + 40 * sin(theta));
			glVertex2i(hexVertex.getx(), hexVertex.gety());
		}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
		for (k = 0; k < 360; k++)
		{
			theta = k ;
			hexVertex.setCoords(circCtr.getx() + 30 * cos(theta), circCtr.gety() + 30 * sin(theta));
			glVertex2i(hexVertex.getx(), hexVertex.gety());
		}
	glEnd();


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
		for (k = 0; k < 360; k++)
		{
			theta = k ;
			hexVertex.setCoords(circCtr.getx() + 20 * cos(theta), circCtr.gety() + 20 * sin(theta));
			glVertex2i(hexVertex.getx(), hexVertex.gety());
		}
	glEnd();



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