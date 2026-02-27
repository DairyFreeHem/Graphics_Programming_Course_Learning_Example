#include <iostream>
#include <GL/glut.h>

typedef float vertex3[3];

// Using your exact 8-point arrays
vertex3 pt[8] = {
    {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0},
    {0,0,1}, {0,1,1}, {1,0,1}, {1,1,1}
};

vertex3 hue[8] = {
    {1,0,0}, {1,0,0}, {0,0,1}, {0,0,1},
    {1,0,0}, {1,0,0}, {0,0,1}, {0,0,1}
};

// Indices to draw two separate 2D squares using the 3D data
// Square 1: vertices 0, 1, 3, 2 (Z=0 plane)
// Square 2: vertices 4, 5, 7, 6 (Z=1 plane - will look identical in 2D)
unsigned int indices[] = {
    0, 1, 3, 2, 
    4, 5, 7, 6
};
GLenum errorCheck(std::string funcName);

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0

    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}


void colorArray(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Enable client-side arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Point to the data
    glVertexPointer(3, GL_FLOAT, 0, pt);
    glColorPointer(3, GL_FLOAT, 0, hue);

    // Draw 2 quads (8 indices total)
    glDrawElements(GL_QUADS, 8, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();

}


int main(int argc, char** argv)
{
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(400,300);       // Set display-window width and height
    glutCreateWindow("An example OpenGL program"); // Create display window
    
    init();                            // Execute initialization procedure
    glutDisplayFunc(colorArray);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}
