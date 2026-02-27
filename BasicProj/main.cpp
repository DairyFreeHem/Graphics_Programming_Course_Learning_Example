#include <iostream>
#include <GL/glut.h>

#define PI 3.1415926539

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0

    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    GLuint regHex;
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    glBegin(GL_LINES);                 // Draw following shape as lines
        glVertex2i(180,15);
        glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);                 // Draw following shape as lines
        glVertex2i(15,180);
        glVertex2i(1145,10);
    glEnd();

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