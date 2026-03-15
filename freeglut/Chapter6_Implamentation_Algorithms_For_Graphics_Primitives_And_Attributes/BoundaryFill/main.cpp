// Fill algorithm example
// To improve this, we might fill the shapes in another thread
// or use another algorithm...

#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <string>



int width = 400, height = 300;

class Vector3FColor {public:
 float r,g,b;
 Vector3FColor(float _r, float _g, float _b): r{_r},g{_g},b{_b}{}

  bool operator==(Vector3FColor other)
 {
    bool red = int(this->r * 10) == int(other.r * 10);
    bool green = int(this->g * 10) == int( other.g * 10);
    bool blue = int(this->b * 10) == int(other.b * 10);
    
    return (red && green && blue);
 }
};

void setPixel(int x, int y, Vector3FColor color);
Vector3FColor getPixelColor(int x, int y);

void boundaryFill4( int x, int y, Vector3FColor fillColor, Vector3FColor borderColor)
{
    Vector3FColor interiorColor  = getPixelColor(x, y);

    if (!(interiorColor == borderColor) && !(interiorColor == fillColor)) {
    
        setPixel(x,y, fillColor);
        boundaryFill4(x+1,y, fillColor,  borderColor);
        boundaryFill4(x-1,y, fillColor,  borderColor);
        boundaryFill4(x,y+1, fillColor,  borderColor);
        boundaryFill4(x,y-1, fillColor,  borderColor);
    }


}

void setPixel(int x, int y, Vector3FColor color)
{
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

Vector3FColor getPixelColor(int x, int y)
{
    // The function doesn't account for relativity between ortho transformation and window size
    GLfloat color[3];
    glReadPixels(x,y,1,1, GL_RGB, GL_FLOAT, color);
    return  Vector3FColor(color[0],color[1],color[2]);
    
}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white  #FFF0

    glMatrixMode(GL_PROJECTION);       // Set Projection parameters ( set projection matrix stack)
    gluOrtho2D(0.0,width,0.0,height);   // Set Orthographic window to 200 x 150 dimension window
}


void writeString(int x, int y,int space, std::string str)
{

    glColor3f(0.0, 0.0, 0.0);
    for (int i  = 0; i  < str.length(); i++) {
        glRasterPos2i(x, y);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
        x += space;
    }
}


// drawing function
// gets called for every screen refresh
void draw (void)
{

    GLuint regHex;
    
    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.
    


    glPolygonMode(GL_FRONT, GL_LINE);   
    glColor3f(0.0,0.0,0.0);            // Set draw color to green

    // Add border around entire window
    glBegin(GL_QUAD_STRIP);
        glVertex2i(1, height-1);
        glVertex2i(1, 1);
        glVertex2i(width, height);
        glVertex2i(width, 0);
    glEnd();
    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        glVertex2i(100,140);
        glVertex2i(0,10);                // Draw following shape as lines
        glVertex2i(200,10);
    glEnd();

    glBegin(GL_TRIANGLES);                 // Draw following shape as lines
        glVertex2i(200,140);
        glVertex2i(150,80);                // Draw following shape as lines
        glVertex2i(250,80);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex2i(300,140);
        glVertex2i(300,80);                // Draw following shape as lines
        glVertex2i(350,140);
        glVertex2i(350,80);
    glEnd();
    

    writeString(10, 280, 8,"Click on shape to draw");
    //boundaryFill4(100, 50,Vector3FColor(1.0,0.5,0.0), Vector3FColor(0,0,0));

    glFlush();                         // Process all OpenGL routines as quickly as possible.
}

void mouseCallback(GLint button, GLint state, GLint x, GLint y)
{

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            boundaryFill4(x, std::abs(y - 300),Vector3FColor(1.0,0.5,0.0), Vector3FColor(0,0,0));

        }
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);             // Init GLUT ( and OpenGL by proxy ).
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50,100);    // Set top-left display window position ( relative to monitor dimensions )
    glutInitWindowSize(width,height);       // Set display-window width and height
    glutCreateWindow("Boundayry fill Algorithm"); // Create display window
    
    init();                            // Execute initialization procedure
    glutDisplayFunc(draw);      // Send graphics to display window ( graphics drawn by lineSegment)
    glutMouseFunc(mouseCallback);
    glutMainLoop();                    // Run program main loop

    return 0;
}