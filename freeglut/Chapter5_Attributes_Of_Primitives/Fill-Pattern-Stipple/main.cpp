// This example shows how to change the draw pattern of a 32 x 32 pixel mask

#include <iostream>
#include <GL/glut.h>


// Draw a 32x32 bit stipple
GLubyte fillPattern [] = {
    0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,
    0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,
    0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,
    0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF,0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF, 0xff, 0xFF
};

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    glEnable(GL_POLYGON_STIPPLE);         // Enable Line style
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    glPolygonStipple(fillPattern);

    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glLineWidth(15.0);
    glColor3f(1.0,0.0,0.0);            // Set draw color to red
    
    glBegin(GL_TRIANGLES);    
        glVertex2i(100,150); 
        glVertex2i(0,0);
        glVertex2i(200,0);
    glEnd();
    glColor3f(0.0,0.0,1.0);
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