#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>


class wcPt2D {
public:
GLfloat x, y;
wcPt2D(GLfloat _x, GLfloat _y): x{_x}, y{_y}{}
wcPt2D(): x{0}, y{0}{}
void renderVertex()
{
    glVertex2f(this->x, this->y);
}
};

wcPt2D triangle[] = {wcPt2D(0.5f,0.5f), wcPt2D(0.3f,0.5f), wcPt2D(0.3f,0.2f)};
wcPt2D triangle2[] = {wcPt2D(0.7f,0.8f), wcPt2D(0.5f,0.5f), wcPt2D(0.7f,0.5f)};
wcPt2D square[] = {wcPt2D(0.7f,0.5f), wcPt2D(0.7f,0.1f), wcPt2D(0.9f,0.1f), wcPt2D(0.9f,0.5f)};
// C trigonometry works with radians
GLdouble rotationTheta = M_PI / 6.0;

// Rotate polygon using a pivot poithnt
// verts - the vertices of the polygon
// nVerts - number of vertices
// pivot - our pivot point
// theta - How many degrees should we rotate
void rotatePolygon(wcPt2D *verts, GLint nVerts, wcPt2D pivot, GLdouble theta)
{
    std::vector<wcPt2D> vertsRot(nVerts);
    for (int k = 0; k < nVerts; k++) {
        vertsRot[k] = verts[k];
    }

    for (GLint k = 0; k < nVerts; k++) {
        // New X coord
        vertsRot[k].x = pivot.x + (verts[k].x -pivot.x) * std::cos(theta) - (verts[k].y - pivot.y) * std::sin(theta);
        // New Y coord
        vertsRot[k].y = pivot.y + (verts[k].x -pivot.x) * std::sin(theta) + (verts[k].y - pivot.y) * std::cos(theta);
    }

    for (int k = 0; k < nVerts; k++) {
        verts[k] = vertsRot[k];
    }

    glBegin(GL_TRIANGLE_FAN);
        for (GLint k = 0; k < nVerts; k++) {
            glVertex2f(vertsRot[k].x, vertsRot[k].y);
        }
    glEnd();
    glFlush();

}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0

    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,1.0,0.0,1.0);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{

    GLuint regHex;

    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    
    glColor3f(1.0,0.4,0.2);     // Set draw color to green
    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        for (int i = 0; i < 3; i++) {
            triangle[i].renderVertex();
        }
    glEnd();

    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        for (int i = 0; i < 3; i++) {
            triangle2[i].renderVertex();
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);                 // Draw following shape as lines
        glVertex2f(square[0].x, square[0].y);
        glVertex2f(square[1].x,square[1].y);
        glVertex2f(square[2].x,square[2].y);
        glVertex2f(square[3].x,square[3].y);
    glEnd();
    glFlush();                                  // Process all OpenGL routines as quickly as possible.
}

void keyboardCallback(int key, int x, int y )
{

    if (key == GLUT_KEY_RIGHT) {
        glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
        rotatePolygon(triangle, 3, triangle[0], -rotationTheta);
        rotatePolygon(triangle2, 3, triangle2[1], -rotationTheta);
        rotatePolygon(square, 4, square[0], -rotationTheta);
    }
    if (key == GLUT_KEY_LEFT) {
        glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
        rotatePolygon(triangle, 3, triangle[0], rotationTheta);
        rotatePolygon(triangle2, 3, triangle2[1], rotationTheta);
        rotatePolygon(square, 4, square[0], rotationTheta);
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
    glutSpecialFunc(keyboardCallback);
    glutMainLoop();                    // Run program main loop

    return 0;
}