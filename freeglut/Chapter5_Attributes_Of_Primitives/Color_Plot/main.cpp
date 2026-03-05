#include <iostream>
#include <GL/glut.h>

typedef struct 
{
    float x;
    float y;
}WcPt2D;

typedef struct 
{
    float r,g,b;
}Color;

GLenum errorCheck(void);


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    glEnable(GL_LINE_STIPPLE);
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}


void linePlot(WcPt2D *dataPts, int length, Color lineColor, GLfloat lineWidth = 2)
{
    glColor3f(lineColor.r,lineColor.g,lineColor.b);
    glLineWidth(lineWidth);
    glBegin(GL_LINE_STRIP);
        for (int k = 0; k < length; k++)
        {
            glVertex2i(dataPts[k].x +2, dataPts[k].y +2);
        }
    glEnd();
}


// drawing function
// gets called for every screen refresh
void draw (void)
{


    //TODO: Read line data from CSV
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.0,0.0);            // Set draw color to red
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glVertex2i(2,150);
        glVertex2i(2,2);
        glVertex2i(2,2);
        glVertex2i(200,2);
    glEnd();
    errorCheck();

    glLineWidth(1.0);


    glLineStipple(1, 0x1C47);
    WcPt2D dataPts[5] = {{1, 2}, {20,20}, {30,30}, {35,20}, {50,50}};
    linePlot(dataPts,5, {1.0,0.0,0.0});


    glFlush();
    
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(400,300);       // Set display-window width and height
    glutCreateWindow("An example OpenGL program"); // Create display window
    
    init();                            // Execute initialization procedure
    glutDisplayFunc(draw);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

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