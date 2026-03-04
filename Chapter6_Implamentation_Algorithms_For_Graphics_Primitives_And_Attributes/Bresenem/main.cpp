// DDA implamentation example
// Try playing with gluOrtho2D values

#include <GL/gl.h>
#include <asm-generic/errno.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

typedef struct {int x,y;} vec2D;

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


// Bresenham example for 0 < m < 1
void lineBresSmall(int x0, int y0, int xEnd, int yEnd, int dx, int dy,int desc = 1)
{

    bool slopeLarge = false;
    int p;
    p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x,y;
    
    // Determine which endpoint to use
    if (x0 > xEnd) 
    {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }
    else 
    {
        x = x0;
        y = y0;
    }
    setPixel(x,y);
    while (x < xEnd) {
        x++; 
        if (p < 0) {
            p += twoDy;
        }
        else {
            y+= 1 * desc; 
            p+= twoDyMinusDx;
        }
        setPixel(x,y);
    }
}

// Bresenham example for m > 1
void lineBresLarge(int x0, int y0, int xEnd, int yEnd,int dx, int dy, int desc)
{
    int p;
    p = 2 * dx - dy;
    int twoDx = 2 * dx;
    int twoDyMinusDx = 2 * (dx - dy);
    int x,y;

    // Determine which endpoint to use
    if (y0 > yEnd) 
    {
        x = xEnd;
        y = yEnd;
        yEnd = y0;
    }
    else 
    {
        x = x0;
        y = y0;
    }
    setPixel(x,y);
    while (y < yEnd) {
        y++;
        if (p < 0) {
            p += twoDx;
        }
        else {
            x+= 1 * desc;
            p+= twoDyMinusDx;
        }
        setPixel(x,y);
    }
}

// Bresenham example, complete with Slopes larger  m > 0 and decreasing slopes
void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd - x0);
    int dy = fabs(yEnd - y0);
    int desc = 1;
    // If line is gowing south-east
    if (yEnd < y0 && xEnd > x0) {
        desc = -1;
    }
    if (dy > dx) {
        // For m > 1
        lineBresLarge(x0, y0, xEnd, yEnd, dx, dy, desc);
    }
    else {
        // For 0 < m < 1
        lineBresSmall(x0, y0, xEnd, yEnd, dx, dy, desc);
    }

}

// Polyline implamentation for Bresenham's algorithm
void polylineBres(std::vector<vec2D> polyline)
{

        vec2D p0 = polyline[0];
        for (int i = 1; i < polyline.size(); i++)
        {
            vec2D p1 = polyline[i];
            lineBres(p0.x, p0.y, p1.x, p1.y);
            p0 = p1;
        }
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    std::vector<vec2D> polyline = { {0,0},{20,40},{100,60},{120,30}, {0,0}};
    // Try resizing the window
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(0.0,0.0,0.0);
    polylineBres(polyline);
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
    glutDisplayFunc(lineSegment);      // Send graphics to display window ( graphics drawn by lineSegment)
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