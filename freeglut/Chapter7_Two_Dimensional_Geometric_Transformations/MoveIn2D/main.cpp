#include <GL/gl.h>
#include <iostream>
#include <GL/glut.h>

class Point
{
    GLint x,y;
    public:
        Point(GLint _x, GLint _y): x{_x}, y{_y}{}
        void addX(int tx)
        {
            x += tx;
        }
        void addY(int ty)
        {
            y += ty;
        }
        GLint getX()
        {
            return  this->x;
        }
        GLint getY()
        {
            return this->y;
        }
};

class Triangle
{
    Point a,b,c;
    public:
        Triangle(Point _a, Point _b, Point _c): a{_a}, b{_b}, c{_c} {}

    void Transform2D(GLint tx, GLint ty)
    {
        this->a.addX(tx);
        this->a.addY(ty);

        this->b.addX(tx);
        this->b.addY(ty);

        this->c.addX(tx);
        this->c.addY(ty);
    }

    void draw()
    {
        glBegin(GL_TRIANGLES);  // Draw following shape as lines
            glVertex2i(this->a.getX(),this->a.getY());
            glVertex2i(this->b.getX(),this->b.getY());
            glVertex2i(this->c.getX(),this->c.getY());
        glEnd();
    }
};


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
    
    Triangle t(Point(180,30),
            Point(150,15),
            Point(180,15));

    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.4,0.2);            // Set draw color to green
    t.draw();

    int x = 0;
    for (int y = 0; y < 100 ; y+= 10) 
    {
        t.Transform2D(x, y);
        t.draw();
        x -= 10;
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
    glutDisplayFunc(lineSegment);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMainLoop();                    // Run program main loop

    return 0;
}