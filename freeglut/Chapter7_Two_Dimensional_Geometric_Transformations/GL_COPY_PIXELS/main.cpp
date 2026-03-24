#include <GL/gl.h>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>


GLenum errorCheck(void);

GLint width = 480, height = 640;

/* Set range for world coordinates. */
GLfloat xwcMin = 0.0, xwcMax = 480.0;
GLfloat ywcMin = 0.0, ywcMax = 640.0;


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


class Rectangle
{
        GLint recWidth = 0;
        GLint recHeight = 0;
    public:
        std::vector<wcPt2D> points;
        GLubyte color[3] = {0,0,0};


        // Constructors
        Rectangle()
        {
            for (int i = 0; i < 4; i++) {
                points.push_back({0.0,0.0});
            }
        }
        Rectangle(std::vector<wcPt2D> _points)
        {
            for (int i = 0; i < 4; i++) {
                points.push_back( _points[i]);
            }
            this->recWidth = this->points[3].x - this->points[0].x;
            this->recHeight = this->points[3].y - this->points[1].y;
        }

        // Copy assignment
        Rectangle& operator=(const Rectangle& other)
        {
            if (this == &other) {
                return *this;
            }
            // Apply copy operator to all other points
            for (int i = 0; i < 4; i++) {
                this->points[i] = { other.points[i]};
            }
            this->setColor(other.color[0], other.color[1], other.color[2]);
            this->recHeight = other.recHeight;
            this->recWidth = other.recWidth;

            return  *this;
        }

        GLint getWidth()
        {
            return this->recWidth;
        }

        GLint getHeight()
        {
            return this->recHeight;
        }
        void setColor(GLubyte red,GLubyte green, GLubyte blue)
        {
            this->color[0] = red;
            this->color[1] = green;
            this->color[2] = blue;
        }

        void copyRectangles(std::vector<wcPt2D> _points)
        {
            for (int i = 0; i < 4; i++) {
                points[i] = { _points[i]};
            }
            this->recWidth = abs(this->points[0].x - this->points[3].x);
            this->recHeight = abs(this->points[0].y - this->points[1].y);
        }

        std::vector<wcPt2D> getRectangleEdges()
        {
            std::vector<wcPt2D> edges = {points[1],points[2]};
            return edges;
        }
        void draw()
        {
            glColor3ub(this->color[0], this->color[0], this->color[0]);
            glBegin(GL_TRIANGLE_STRIP);
                for (int i = 0; i < 4; i++) {
                    glVertex2f(points[i].x,points[i].y);
                }
            glEnd();
        }
};


Rectangle rec;


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0
    errorCheck();
    wcPt2D point1 (20.0,300.0);
    wcPt2D point2 (20.0,100.0);
    wcPt2D point3 (100.0,100.0);
    wcPt2D point4 (100.0,300.0);
    std::vector<wcPt2D> pts = {point1,point2,point4,point3};
    rec.copyRectangles(pts);
}


// drawing function
// gets called for every screen refresh

void lineSegment (void)
{

    GLuint regHex;
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.4,0.2);            // Set draw color to green

    rec.draw();

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


void moveRectangle(Rectangle rectangle, GLfloat horizOffset, GLfloat vertOffset, GLfloat size)
{
     std::vector<wcPt2D> edges = rectangle.getRectangleEdges();
     lineSegment();
     glRasterPos2f(edges[0].x + horizOffset, edges[0].y + vertOffset);
     glPixelZoom(size, size);

     glCopyPixels(edges[0].x, edges[0].y, rec.getWidth(), rec.getHeight(), GL_COLOR);
     glFlush();
}

// Move object
void specialFunc(int key, int x, int y)
{
    static GLfloat movementOffset = 0.0;
    static GLfloat vertOffset = 0.0;
    static GLfloat size = 1.0;
    if (key == GLUT_KEY_RIGHT) {
        movementOffset += 20.0;
        moveRectangle(rec, movementOffset,vertOffset,size);
    }
    else if (key == GLUT_KEY_LEFT) {
        movementOffset -= 20.0;
        moveRectangle(rec, movementOffset,vertOffset,size);    
    }
    else if (key == GLUT_KEY_UP) {
        vertOffset += 20.0;
        moveRectangle(rec, movementOffset,vertOffset,size);
    }
    else if (key == GLUT_KEY_DOWN) {
        vertOffset -= 20.0;
        moveRectangle(rec, movementOffset,vertOffset,size);
    }
    else if(key == GLUT_KEY_F1) {
        size += 0.1;
        moveRectangle(rec, movementOffset,vertOffset,size); 
    }
    else if(key == GLUT_KEY_F2) {
        if (size > 0.5) {
            size -= 0.1;
        }
        moveRectangle(rec, movementOffset,vertOffset,size); 
    }
    
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(width,height);       // Set display-window width and height
    glutCreateWindow("GL Raster Pixel Copy"); // Create display window
    errorCheck();
    
    init();                            // Execute initialization procedure
    glutReshapeFunc(windowReshapeFunction);
    glutDisplayFunc(lineSegment);      // Send graphics to display window ( graphics drawn by lineSegment)
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