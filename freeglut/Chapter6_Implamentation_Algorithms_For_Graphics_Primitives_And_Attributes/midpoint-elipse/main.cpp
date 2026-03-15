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


inline int round (const float a) { return int(a+0.5);}


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
void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
    setPixel(xCenter + x, yCenter + y);
    setPixel(xCenter - x, yCenter + y);
    setPixel(xCenter + x, yCenter - y);
    setPixel(xCenter - x, yCenter - y);
}


void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry)
{
    int Rx2 = Rx * Ry;
    int Ry2 = Rx * Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2 * y;
    ellipsePlotPoints(xCenter, yCenter, x, y);

    // Region 1
    p = round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py){
        x++;
        px += twoRy2;
        if (p < 0) {
            p += Ry2 + px;
        }
        else {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }

    // Region 2
    p = round(Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
    while (y > 0){
        y--;
        py -= twoRx2;
        if (p > 0) {
            p += Rx2 - py;
        }
        else {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }
}

// drawing function
// gets called for every screen refresh
void circleSegment (void)
{
    // Try resizing the window
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(0.0,0.0,0.0);

    ellipseMidpoint(50,50, 10,5);
        glColor3f(1.0,0.0,0.0);
    ellipseMidpoint(50,100, 5,10);
        glColor3f(0.0,1.0,0.0);
    ellipseMidpoint(50,20, 5,5);
        glColor3f(0.0,0.0,1.0);
    ellipseMidpoint(20,50, 20,10);

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