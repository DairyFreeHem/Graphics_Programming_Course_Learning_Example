// DDA implamentation example
// Try playing with gluOrtho2D values

#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

typedef struct {int x,y;} vec2D;

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    glEnable(GL_LINE_STIPPLE);         // Enable Line style
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

// DDA example
void lineDDA(int x0, int y0, int x1, int y1)
{
    int steps, k;
    int dx = x1 - x0;
    int dy = y1 - y0;
    float xIncrement, yIncrement, x = x0, y = y0;
    if (fabs(dx) > fabs(dy))                   // |m| > 1
        steps = fabs(dx);
    else
        steps = fabs(dy);                         // |m| < 1
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);
    setPixel(round(x), round(y));  
    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
    
}

void polylineDDA(std::vector<vec2D> polyline)
{

        vec2D p0 = polyline[0];
        for (int i = 1; i < polyline.size(); i++)
        {
            vec2D p1 = polyline[i];
            lineDDA(p0.x, p0.y, p1.x, p1.y);
            p0 = p1;
        }
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    std::vector<vec2D> polyline = { {0,0},{20,40},{100,60},{120,30}, };
    // Try resizing the window
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(0.0,0.0,0.0);
    polylineDDA(polyline);
    // lineDDA(0,0,20,40);
    // lineDDA(20,40,100,60);
    // lineDDA(100,60,120,30);
    // lineDDA(120,30,0,0);
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