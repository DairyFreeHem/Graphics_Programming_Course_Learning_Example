///
/// Implamentation of a color + vertex array using one unified array
///

#include <iostream>
#include <GL/glut.h>


static GLint hueAndPt[] = {
    1,0,0,0,0,0,1,0,0,0,1,0,
    0,0,1,1,0,0,0,0,1,1,1,0,
    1,0,0,0,0,1,1,0,0,0,1,1,
    0,0,1,1,0,1,0,0,1,1,1,1};


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
    glVertexPointer(3, GL_INT, 6*sizeof(GLint), &hueAndPt[3]);
    glColorPointer(3, GL_INT, 6*sizeof(GLint), &hueAndPt[0]);



    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glFlush();

}


int main(int argc, char** argv)
{
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
