#include<GL/glut.h>


GLubyte bitShape [20] = {
0x1c, 0x0F,
0x1c, 0x0F, 
0x1c, 0x0F, 
0x1c, 0x0F, 
0x1c, 0x0F,
0xff, 0x8F, 
0x7f, 0x0F, 
0x3e, 0x0F, 
0x1c, 0x0F, 
0x08, 0x00};



void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}


void drawBitmap(void)
{

    glClear (GL_COLOR_BUFFER_BIT);     // Clear display window.

    glColor3f(0.0,0.0,0.0);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glRasterPos2i(30,40);
    glBitmap(16,10,0.0,0.0,20.0,15.0,bitShape);

    glRasterPos2i(90,40);
    glBitmap(15,10,0.0,0.0,20.0,15.0,bitShape);

    glFlush();


}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("Test Bitmaps");

    init();
    glutDisplayFunc(drawBitmap);
    glutMainLoop();
}