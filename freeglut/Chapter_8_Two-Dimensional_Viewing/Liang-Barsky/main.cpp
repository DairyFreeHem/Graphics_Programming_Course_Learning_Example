#include <GL/gl.h>
#include <iostream>
#include <GL/glut.h>


class wcPt2D{

    public:
        GLfloat x,y;
        wcPt2D(GLfloat _x, GLfloat _y): x{_x}, y{_y}{}
        wcPt2D(){}
        wcPt2D(const wcPt2D& other): x{other.x}, y{other.y}{}
        wcPt2D& operator=(const wcPt2D& other)
        {
            if (this == &other) {
                return  *this;
            }
            this->x = other.x;
            this->y = other.y;
            return *this;
        }
};

typedef struct ClipWindow
{
    GLfloat x,y,width,height;
}ClipWindow;

GLint width = 480, height = 640;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 480.0;
GLfloat ywcMin = 0.0, ywcMax = 640.0;

ClipWindow cWindow = {50,50,100,100};

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;



GLenum errorCheck(void);






inline GLint round (const GLfloat a)
{
    return GLint(a + 0.5);
}

GLint clipTest( GLfloat p, GLfloat q, GLfloat *u1, GLfloat *u2)
{
    GLfloat r;
    GLint returnValue = true;
    // If line goes from outside to inside
    if (p < 0.0)
    {
        r = q/p;
        
        // If point is outside of clip window
        if (r > *u2) {
            returnValue = false;
        }
        // If point is in clip window and more inside than current u2
        else if(r > *u1) {
            *u1 = r;
        }
    }
    else if ( p > 0.0)
    {
        r = q/p;
        
        // If point is outside of clip window
        if (r < *u1) {
            returnValue = false;
        }
        // If point is in clip window and more inside than current u2
        else if (r < *u2)
        {
            *u2 = r;
        }
    }
    else if (q < 0.0)
    {
        returnValue = false;
    }
    return returnValue;

}


void LineClip(ClipWindow clipWindow, wcPt2D p1, wcPt2D p2)
{
    GLfloat clipWindowXMax = clipWindow.x + clipWindow.width;
    GLfloat clipWindowYMax = clipWindow.y + clipWindow.height;

    GLfloat u1 = 0.0, u2 = 1.0;
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;

    GLfloat q1 = p1.x - clipWindow.x;
    GLfloat q2 = clipWindowXMax - p1.x;
    GLfloat q3 = p1.y - clipWindow.y;
    GLfloat q4 = clipWindowYMax - p1.y;

    // Left
    if (clipTest(-dx, q1, &u1, &u2)) {
        // Right
        if (clipTest(dx, q2, &u1, &u2)) {
            // Top
            if (clipTest(-dy, q3,&u1 , &u2)) {
                // Bottom
                if (clipTest(dy, q4, &u1, &u2)) {
                    if (u2 < 1.0) {
                        p2 = {p1.x + (u2 * dx), p1.y + (u2 * dy)};
                    }
                    if (u1 > 0.0) {
                        p1 = {p1.x + (u1 * dx), p1.y + (u1 * dy)};
                    }
                    glBegin(GL_LINES);
                    glVertex2f(round(p1.x), round(p1.y));
                    glVertex2f(round(p2.x),round(p2.y));
                    glEnd();
                }
            }
        
        }
    }


}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    errorCheck();
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    errorCheck();
    gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);   // Set Orthographic window to 200 x 150 dimension window
}
// drawing function
// gets called for every screen refresh
void draw (void)
{
    wcPt2D line1[2] = {{25,50},{200,100}};
    wcPt2D line2[2] = {{0,0},{xwcMax,ywcMax}};
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.0,0.0);            // Set draw color to green
    glBegin(GL_LINE_STRIP);                 // Draw following shape as lines
        glVertex2f(cWindow.x,cWindow.y + cWindow.height);
        glVertex2f(cWindow.x, cWindow.y);
        glVertex2f(cWindow.x+cWindow.width,cWindow.y);
        glVertex2f(cWindow.x + cWindow.width,cWindow.y + cWindow.height);
        glVertex2f(cWindow.x,cWindow.y + cWindow.height);
    glEnd();

    LineClip(cWindow, line1[0], line1[1]);
    LineClip(cWindow, line2[0], line2[1]);

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}

void windowReshapeFunction(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    
    // Viewport aided using Gemini
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    glLoadIdentity();
    gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax); 
}


void keyboardFunc(unsigned char key, int x, int y)
{

}

void specialFunc(int key, int x, int y)
{

    if (key == GLUT_KEY_RIGHT) {
        cWindow.x += 2;
    }
    if (key == GLUT_KEY_LEFT) {
        cWindow.x -= 2;
    }
    if (key == GLUT_KEY_UP) {
        cWindow.y += 2;
    }
    if (key == GLUT_KEY_DOWN) {
        cWindow.y -= 2;
    }
    draw();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(width,height);       // Set display-window width and height
    glutCreateWindow("An example OpenGL program"); // Create display window
    errorCheck();
    
    init();                            // Execute initialization procedure
    glutReshapeFunc(windowReshapeFunction);
    glutDisplayFunc(draw);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutMainLoop();                    // Run program main loop

    return 0;
}


GLenum errorCheck(void)
{
	GLenum code;
	const GLubyte* errStr;

	code = glGetError();
	if (code != GL_NO_ERROR)
	{
		errStr = gluErrorString(code);
		std::cerr << "OpenGL error: " << errStr;
	}
	return code;
}