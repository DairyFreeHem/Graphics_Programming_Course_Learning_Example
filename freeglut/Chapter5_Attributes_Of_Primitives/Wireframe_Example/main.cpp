#include <iostream>
#include <GL/glut.h>

static bool wireframeMode = false;

const std::string label = "Q - Wireframe Mode";

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
    if (wireframeMode)
    {
        glPolygonMode(GL_FRONT, GL_LINE);   
    }
    else
    {
        glPolygonMode(GL_FRONT, GL_FILL);
    }
    


    glColor3f(0.0,0.0,0.0);            // Set draw color to green
    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        glVertex2i(100,140);
        glVertex2i(0,10);                // Draw following shape as lines
        glVertex2i(200,10);
    glEnd();

    GLint xPos = 5;
    for (GLint i = 0; i < label.size(); i++)
    {
        glRasterPos2i(xPos, 140);
        // Add extra padding for capiral letters
        if (label[i] >= 65 && label[i] <= 90)
        {
            xPos += 2;
        }
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,label[i]);

        
        xPos += 4;
    }
    

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}

void keyboard(unsigned char key, int mouse_X, int mouse_Y)
{

    if (key == 'q' || key == 'Q')
    {
        wireframeMode = !wireframeMode;
        lineSegment();
    }
    

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
    glutKeyboardFunc(keyboard);        // Input function
    glutMainLoop();                    // Run program main loop

    return 0;
}