#include <GL/gl.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>


GLenum errorCheck(void);

GLint width = 480, height = 640;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 480.0;
GLfloat ywcMin = 0.0, ywcMax = 640.0;

GLfloat buttonX = 250.0,buttonY = 100.0;
GLfloat buttonWidth = 100, buttonHeight = 80;

int mainWindow;
std::vector<int> subWindows;

void initMain(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    errorCheck();
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    errorCheck();
    gluOrtho2D(xwcMin,xwcMax,ywcMin,ywcMax);   // Set Orthographic window to 200 x 150 dimension window
}

void initSub(void)
{
    glClearColor (0.0, 0.5, 0.5, 0.0); // Set display-window color to white  #FFF0
    errorCheck();
    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    errorCheck();
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
    gluOrtho2D(0,300,0,300);   // Set Orthographic window to 200 x 150 dimension window
}

// drawing function
// gets called for every screen refresh
void drawMain (void)
{
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    glBegin(GL_QUADS);                 // Draw following shape as lines
        glVertex2f(buttonX , buttonY + buttonHeight);
        glVertex2f(buttonX, buttonY);
        glVertex2f(buttonX + buttonWidth, buttonY);
        glVertex2f(buttonX + buttonWidth, buttonY + buttonHeight);

    glEnd();

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}

void drawSub (void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    std::string str = "Hello Smaller World!";
    glColor3f(0.0,0.0,0.0);            // Set draw color to green
    glRasterPos2f(10.0, 10.0);
    for (auto k = 0; k <str.length(); k++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[k]);
    }

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

int main(int argc, char** argv)
{
    subWindows = {};
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(width,height);       // Set display-window width and height
    mainWindow = glutCreateWindow("An example OpenGL program"); // Create display window
    errorCheck();

    initMain();                            // Execute initialization procedure
    glutReshapeFunc(windowReshapeFunction);
    glutDisplayFunc(drawMain);      // Send graphics to display window ( graphics drawn by lineSegment)

    
    // Create new window inside main window
    int subWindow = glutCreateSubWindow(mainWindow, 100,100, 300, 300);
    errorCheck();
    subWindows.push_back(subWindow); // Store subWindow id
    initSub();
    glutDisplayFunc(drawSub);
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