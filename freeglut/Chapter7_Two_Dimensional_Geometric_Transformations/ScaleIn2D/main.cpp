#include <cmath>
#include <vector>
#include <GL/glut.h>



#define ONE_SIXTH 0.166666667
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
// C trigonometry works with radians
GLdouble rotationTheta = M_PI / 6.0;

// Find the centroid of an object
// We use this function to keep pur resize function from moving the object
wcPt2D findCentroid(wcPt2D *verts, GLint nVerts)
{
    wcPt2D centroid;
    float area = (verts[0].x * verts[1].y - verts[1].x * verts[0].y );
    centroid.x = (verts[1].x + verts[0].x) * (verts[0].x * verts[1].y - verts[1].x * verts[0].y ) ;
    centroid.y= (verts[1].y + verts[0].y) * (verts[0].x * verts[1].y - verts[1].x * verts[0].y ) ;
    if (nVerts > 2) {
        for (GLint k = 1; k < nVerts- 1; k++) {
        centroid.x += (verts[k+1].x + verts[k].x) * (verts[k].x * verts[k+1].y - verts[k+1].x * verts[k].y ) ;
        centroid.y += (verts[k+1].y + verts[k].y) * (verts[k].x * verts[k+1].y - verts[k+1].x * verts[k].y ) ;
        area += (verts[k].x * verts[k+1].y - verts[k+1].x * verts[k].y ) ;
        }
        // Connet the final vertex with the first one
        centroid.x += (verts[0].x + verts[nVerts-1].x) * (verts[nVerts-1].x * verts[0].y - verts[0].x * verts[nVerts-1].y ) ;
        centroid.y += (verts[0].y + verts[nVerts-1].y) * (verts[nVerts-1].x * verts[0].y - verts[0].x * verts[nVerts-1].y ) ;
        area += (verts[nVerts-1].x * verts[0].y - verts[0].x * verts[nVerts-1].y ) ;
    }
    area *= 0.5;
    centroid.x *= (ONE_SIXTH);
    centroid.y *= (ONE_SIXTH);
    if (area != 0) {
        centroid.x /= area;
        centroid.y /= area;
    }
    
    return  centroid;
}

// Rotate polygon using a pivot poithnt
// verts - the vertices of the polygon
// nVerts - number of vertices
// pivot - our pivot point
// theta - How many degrees should we rotate
void scalePolygon(wcPt2D *verts, GLint nVerts, GLfloat sx, GLfloat sy)
{
    wcPt2D fixedPoint = findCentroid(verts,nVerts);
    std::vector<wcPt2D> vertsNew(nVerts);
    for (int k = 0; k < nVerts; k++) {
        vertsNew[k] = verts[k];
    }

    for (GLint k = 0; k < nVerts; k++) {
        vertsNew[k].x = verts[k].x * sx + fixedPoint.x * (1-sx);
        vertsNew[k].y = verts[k].y * sy + fixedPoint.y * (1-sy);
    }

    for (int k = 0; k < nVerts; k++) {
        verts[k] = vertsNew[k];
    }

    glBegin(GL_TRIANGLE_FAN);
        for (GLint k = 0; k < nVerts; k++) {
            glVertex2f(vertsNew[k].x, vertsNew[k].y);
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


    wcPt2D cent = findCentroid(triangle, 3);

    glColor3f(0,1.0,0);     // Set draw color to green
    
    glColor3f(1.0,0.4,0.2);     // Set draw color to green
    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        for (int i = 0; i < 3; i++) {
            triangle[i].renderVertex();
        }
    glEnd();

    glFlush();                                  // Process all OpenGL routines as quickly as possible.
}

void keyboardCallback(int key, int x, int y )
{

    if (key == GLUT_KEY_UP) {
        glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
        scalePolygon(triangle, 3, 2,2);
    }
    if (key == GLUT_KEY_DOWN) {
        glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
        scalePolygon(triangle, 3, 0.5,0.5);
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