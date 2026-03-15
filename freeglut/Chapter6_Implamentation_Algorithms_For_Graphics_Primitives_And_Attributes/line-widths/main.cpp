// Midpoint circle implementation example

#include <GL/gl.h>
#include <asm-generic/errno.h>
#include <iostream>
#include <GL/glut.h>


class screenPt
{
    	private:
		GLint x, y;
	public:
        screenPt(void)
        {
            this->x = this->y = 0;
        }
        screenPt(int _x, int _y): x{_x}, y{_y}
        {}

        void setCoords(GLint xCoord, GLint yCoord)
        {
            this->x = xCoord;
            this->y = yCoord;
        }

        GLint getx(void) const
        {
            return this->x;
        }

        GLint gety(void) const
        {
            return this->y;
        }

        void incX(void)
        {
            this->x++;
        }
        void incY(void)
        {
            this->y++;
        }
        void decX(void)
        {
            this->x--;
        }

        void decY(void)
        {
            this->y--;
        }

};


inline int round (const float a) { return int(a+0.5);}


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);   // Set display-window color to white  #FFF0
    glEnable(GL_LINE_STIPPLE);                             // Enable Line style
    glMatrixMode(GL_PROJECTION);                          // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,200.0,0.0,150.0);   // Set Orthographic window to 200 x 150 dimension window
}

void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

/// Draw line with thickness, generated using Gemini
void drawThickLine(int x0, int y0, int x1, int y1, int width) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    // Calculate centering offsets
    int offset_min = -(width - 1) / 2;
    int offset_max = offset_min + width;

    while (true) {
        // PERPENDICULAR REPLICATION
        // If line is horizontal-ish (slope < 1), stack pixels vertically
        if (dx > dy) {
            for (int i = offset_min; i < offset_max; ++i) {
                setPixel(x0, y0 + i);
            }
        } 
        // If line is vertical-ish (slope >= 1), stack pixels horizontally
        else {
            for (int i = offset_min; i < offset_max; ++i) {
                setPixel(x0 + i, y0);
            }
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// drawing function
// gets called for every screen refresh
void lineSegment (void)
{
    // Try resizing the window
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(0.0,0.0,0.0);

    drawThickLine(20, 50, 50, 100, 10);

    drawThickLine(100, 50, 130, 70, 10);
    // M = 1, line is thicker
    drawThickLine(70, 80, 90, 100, 10);

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
    glutDisplayFunc(lineSegment);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}

GLenum errorCheck(void)
{
	GLenum cod;
	const GLubyte* errStr;

	cod = glGetError();
	if (cod != GL_NO_ERROR)
	{
		errStr = gluErrorString(cod);
		std::cerr << "OpenGL error: " << errStr;
	}
	return cod;
}