#include <GL/gl.h>
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


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0

    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,600.0,0.0,500.0);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void lineGraph (void)
{
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    GLint month, k;
    GLint x = 30;

    glColor3f(0.0, 0.0,1.0);
    
    glBegin(GL_LINE_STRIP);
        for (k = 0; k < 12; k++) {
            glVertex2i(x + k*50 , dataValue[k]);
        }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    for (k = 0; k < 12; k++) {
        glRasterPos2i(xRaster + k * 50, dataValue[k] - 4);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
    }

    glColor3f(0.0, 0.0, 0.0);
    xRaster = 20;
    for (month = 0; month < 12; month++) {
        glRasterPos2i(xRaster, yRaster);
        for (k = 3 * month; k < 3 * month + 3; k++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
            xRaster += 50;
        }
    }

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
    glutDisplayFunc(lineGraph);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}