#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

/* Set initial display-window size. */
GLsizei winWidth = 600, winHeight = 600;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

class wcPt2D{

    public:
        GLfloat x,y;
        wcPt2D(GLfloat _x, GLfloat _y): x{_x}, y{_y}{}
        wcPt2D(){}
};

typedef GLfloat Matrix3x3 [3][3] ;
Matrix3x3 matComposite;


void init (void)
{
/* Set color of display window to white. */
glClearColor (1.0, 1.0, 1.0, 0.0);
}

/* Construct the 3 x 3 identity matrix. */
void matrix3x3SetIdentity (Matrix3x3 matIdent3x3)
{
GLint row, col;
    for (row = 0; row < 3; row++)
    {
        for (col = 0; col < 3; col++)
        {
        matIdent3x3 [row][col] = (row == col);
        }
    }
}

/* Construct the 3 x 3 identity matrix. */
void matrix3x3PreMultiply (Matrix3x3 m1,Matrix3x3 m2 )
{
    Matrix3x3 matTemp;

    for (GLint row = 0; row < 3; row++) {
        for (GLint col = 0; col < 3; col++) {
            matTemp [row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
        }
    }

    for (GLint row = 0; row < 3; row++) {
        for (GLint col = 0; col < 3; col++) {
            m2[row][col] = matTemp[row][col];
        }
    }

}

void translate2D(GLfloat tx, GLfloat ty)
{
    Matrix3x3 transformationMat;

    // Init matrix as identity matrix
    matrix3x3SetIdentity(transformationMat);

    transformationMat[0][2] = tx;
    transformationMat[1][2] = ty;

    // Multiply matrix with composite
    matrix3x3PreMultiply(transformationMat, matComposite);
}

// Create + multiply roataion matrix
void rotate2D(wcPt2D pivotPt, GLfloat theta)
{
    Matrix3x3 rotationMat;

    // Init matrix as identity matrix
    matrix3x3SetIdentity(rotationMat);

    // Fill first row of matrix
    rotationMat[0][0] = std::cos(theta);
    rotationMat[0][1] = -std::sin(theta);
    rotationMat[0][2] = pivotPt.x * (1- std::cos(theta)) + pivotPt.y * std::sin(theta);
    
    rotationMat[1][0] = std::sin(theta);
    rotationMat[1][1] = std::cos(theta);
    rotationMat[1][2] = pivotPt.y * (1- std::cos(theta)) - pivotPt.x * std::sin(theta);

    
    // Multiply matrix with composite
    matrix3x3PreMultiply(rotationMat, matComposite);
}

void scale2D(GLfloat sx, GLfloat sy, wcPt2D fixedPt)
{
    Matrix3x3 scaleMat;
    matrix3x3SetIdentity(scaleMat);

    scaleMat[0][0] = sx;
    scaleMat[0][2] = (1-sx) * fixedPt.x;
    scaleMat[1][1] = sy;
    scaleMat[1][2] = (1-sy) * fixedPt.y;

    matrix3x3PreMultiply(scaleMat, matComposite);
}

void triangle(wcPt2D *verts)
{
    glBegin(GL_TRIANGLES);
    for(GLint k = 0; k < 3; k++)
    {
        glVertex2f(verts[k].x, verts[k].y);
    }
    glEnd();
}

void transformVerts2D(GLint nVerts, wcPt2D *verts)
{
    GLfloat temp;
    for (GLint k = 0; k < nVerts; k++) {
        temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
        verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
        verts[k].x = temp;
    }
}

void draw(void)
{
    GLint nVerts = 3;
    wcPt2D verts[3] = {{50.0,25.0},{150.0,25.0},{100.0,100.0}};

    // Calculate centroid
    wcPt2D centroidPt;

    GLint xSum = 0, ySum = 0;
    for (GLint k = 0; k < nVerts; k++) {
        xSum += verts[k].x;
        ySum += verts[k].y;
    }
    centroidPt.x = GLfloat (xSum) / GLfloat(nVerts);
    centroidPt.y = GLfloat (ySum) / GLfloat(nVerts);

    wcPt2D pivPt, fixedPt;
    pivPt = centroidPt;
    fixedPt = centroidPt;

    GLfloat tx = 0.0, ty = 100.0;
    GLfloat sx = 0.5, sy = 0.5;
    GLdouble theta = M_PI / 2.0;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    triangle(verts);

    matrix3x3SetIdentity(matComposite);

    scale2D(sx, sy, fixedPt);
    rotate2D(pivPt, theta);
    translate2D(tx, ty);
    transformVerts2D(nVerts, verts);

    glColor3f(1.0, 0.0,0.0);
    triangle(verts);
    glFlush();
}

void reshapeFunc(GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

    glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(winWidth,winHeight);       // Set display-window width and height
    glutCreateWindow("Matrix Composite Example"); // Create display window
    
    init();                            // Execute initialization procedure
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(draw);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}