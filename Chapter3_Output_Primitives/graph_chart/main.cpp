#include <iostream>
#include <GL/glut.h>

GLsizei minWidth = 600, winHeight = 500; // Init display window size
GLint xRaster = 25, yRaster = 150;       // Init raster position

GLubyte label [36] = {'J', 'a', 'n', 'F', 'e', 'b', 'M', 'a', 'r',
                        'A', 'p', 'r', 'M', 'a', 'y', 'J', 'u', 'n',
                        'J', 'u', 'l', 'A', 'u', 'g', 'S', 'e', 'p',
                        'O', 'c', 't', 'N', 'o', 'v', 'D', 'e', 'c'};

GLint dataValue [12] = {420, 342, 324, 310, 262, 185,
190, 196, 217, 240, 312, 438};

GLubyte bitShape [20] = {
0x1c, 0x00, 
0x1c, 0x00,
0x1c, 0x00, 
0x1c, 0x00, 
0x1c, 0x00,
0xff, 0x80, 
0x7f, 0x00, 
0x3e, 0x00,
0x1c, 0x00, 
0x08, 0x00};


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

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    glBegin(GL_LINES);                 // Draw following shape as lines
        glVertex2i(180,15);
        glVertex2i(10,145);
    glEnd();

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}

void drawLineBitmap(void)
{
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1); // Set Pixel mode
    glRasterPos2i(20,40);
    glBitmap (9, 10, 0.0, 0.0, 20.0, 15.0, bitShape);
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
    glutDisplayFunc(drawLineBitmap);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}