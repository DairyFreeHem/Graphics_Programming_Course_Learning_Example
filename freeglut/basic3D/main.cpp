
/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

// Edit in 2026: Lighting and colors removed

#include <GL/gl.h>
#include <GL/glut.h>



GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, 
  {0.0, 1.0, 0.0},
  {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, 
  {0.0, 0.0, 1.0}, 
  {0.0, 0.0, -1.0} 
};
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void
drawBox(void)
{
  int i;

  glColor3f(0.0,0.0,0.0);

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}

void
init(void)
{
  /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;



    glClearColor (1.0, 1.0, 1.0, 0.0);          // Set display-window color to white  #FFF0


  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(70, 1.0, 0.0, 0.0); // Rotate by X axis
  glRotatef(-20, 0.0, 0.0, 1.0);

    glPolygonMode(GL_FRONT, GL_LINE);   
    glPolygonMode(GL_BACK, GL_LINE);  
}

void specialFunc(int key, int x , int y)
{


    static int angleZ = 70;
    static int angleX = 70;
    if(key==GLUT_KEY_RIGHT)
    {
        angleZ+= 0.5;
        glMatrixMode(GL_MODELVIEW);
        glRotatef(angleZ, 0.0, 0.0, 0.5);
        display();
    }
    if(key==GLUT_KEY_LEFT)
    {
        angleZ+= 0.5;
        glMatrixMode(GL_MODELVIEW);
        glRotatef(angleZ, 0.0, 0.0, -0.5);
        display();
    }
    if(key==GLUT_KEY_UP)
    {
        angleX+= 0.5;
        glMatrixMode(GL_MODELVIEW);
        glRotatef(angleX, 0.5, 0.0, 0.0);
        display();
    }
    if(key==GLUT_KEY_DOWN)
    {
        angleX+= 0.5;
        glMatrixMode(GL_MODELVIEW);
        glRotatef(angleX, -0.5, 0.0, 0.0);
        display();
    }
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
  glutCreateWindow("3D cube example");
  glutDisplayFunc(display);
  glutSpecialFunc(specialFunc);
  init();
  glutMainLoop();
  return 0;
}
