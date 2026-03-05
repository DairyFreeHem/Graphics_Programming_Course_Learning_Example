#include <iostream>
#include <GL/glut.h>


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
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(1.0,0.0,0.0);            // Set draw color to red
    glLineWidth(2.0);
    glLineStipple(15, 0x000);
    glBegin(GL_LINES);    
        glVertex2i(50,100); 
        glVertex2i(100,100);
    glEnd();

    glColor3f(0.0,1.0,0.0); 
    glLineWidth(5.0);
    glBegin(GL_LINES);    
        glVertex2i(80,90); 
        glVertex2i(130,90);
    glEnd();

    glColor3f(0.0,0.0,1.0); 
    glLineWidth(10.0);

    glBegin(GL_LINES);    
        glVertex2i(100,80); 
        glVertex2i(150,80);
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