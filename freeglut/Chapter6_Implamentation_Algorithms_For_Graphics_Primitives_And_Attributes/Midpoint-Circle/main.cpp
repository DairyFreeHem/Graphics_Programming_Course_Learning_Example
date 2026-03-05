// Midpoint circle implementation example

#include <GL/gl.h>
#include <asm-generic/errno.h>
#include <iostream>
#include <GL/glut.h>


class screenPt
{
    	private:
		GLint x, y;
	public:
        screenPt(void)
        {
            this->x = this->y = 0;
        }
        screenPt(int _x, int _y): x{_x}, y{_y}
        {}

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

        void incX(void)
        {
            this->x++;
        }
        void incY(void)
        {
            this->y++;
        }
        void decX(void)
        {
            this->x--;
        }

        void decY(void)
        {
            this->y--;
        }

};


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);   // Set display-window color to white  #FFF0
    glEnable(GL_LINE_STIPPLE);                             // Enable Line style
    glMatrixMode(GL_PROJECTION);                          // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// Draw first octet of circle, when circPt = (0,r)
void circlePlotFirstOctal(GLint xc, GLint yc, screenPt circPt)
{
    setPixel(xc + circPt.getx(), yc + circPt.gety());
    setPixel(xc - circPt.getx(), yc + circPt.gety());
    setPixel(xc + circPt.getx(), yc - circPt.gety());
    setPixel(xc - circPt.getx(), yc - circPt.gety());
    // Reverse x and y
    setPixel(xc + circPt.gety(), yc + circPt.getx());
    setPixel(xc - circPt.gety(), yc + circPt.getx());
    setPixel(xc + circPt.gety(), yc - circPt.getx());
    setPixel(xc - circPt.gety(), yc - circPt.getx());
}


void circleMidpoint(GLint xc, GLint yc, GLint radius)
{

    screenPt circPt {0,radius};
    GLfloat p = (5/4) - radius; // use float version of decision
    circlePlotFirstOctal(xc, yc, circPt);

    while (circPt.getx() < circPt.gety()) {
        circPt.incX();
        if (p < 0) {
            p += 2 * circPt.getx() + 1;
        }
        else {
            circPt.decY();
            p += 2 * (circPt.getx() - circPt.gety()) + 1;
        }
        circlePlotFirstOctal(xc,yc,circPt);
    }
}

// drawing function
// gets called for every screen refresh
void circleSegment (void)
{
    // Try resizing the window
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(0.0,0.0,0.0);

    circleMidpoint(50,50, 40);
        glColor3f(1.0,0.0,0.0);
    circleMidpoint(50,50, 30);
        glColor3f(0.0,1.0,0.0);
    circleMidpoint(50,50, 20);
        glColor3f(0.0,0.0,1.0);
    circleMidpoint(50,50, 10);

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(400,300);       // Set display-window width and height
    glutCreateWindow("An example OpenGL program"); // Create display window
    
    init();                            // Execute initialization procedure
    glutDisplayFunc(circleSegment);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}

GLenum errorCheck(void)
{
	GLenum cod;
	const GLubyte* errStr;

	cod = glGetError();
	if (cod != GL_NO_ERROR)
	{
		errStr = gluErrorString(cod);
		std::cerr << "OpenGL error: " << errStr;
	}
	return cod;
}