
#include <GL/gl.h>
#include <GL/glut.h>

class Cube
{
  GLfloat x,y,z, width, height, depth;

  public:
    Cube(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _width, GLfloat _height, GLfloat _depth): x{_x},y{_y},z{_z},width(_width),height(_height),depth(_depth)
    {}
    
    void draw()
    {
      // Bottom
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(this->x, this->y, this->z);
      glVertex3f((this->x + this->depth), this->y, this->z);
      glVertex3f((this->x + this->depth), (this->y + this->width), this->z);
      glVertex3f((this->x), (this->y + this->width), this->z);
      glEnd();


      // Top
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(this->x, this->y, (this->z + height));
      glVertex3f((this->x + this->depth), this->y, (this->z + height));
      glVertex3f((this->x + this->depth), (this->y + this->width), (this->z + height));
      glVertex3f((this->x), (this->y + this->width), (this->z + height));
      glEnd();

      // Sides
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(this->x, this->y, (this->z + height));
      glVertex3f(this->x, this->y, this->z);
      glVertex3f((this->x + this->depth), this->y, this->z);
      glVertex3f((this->x + this->depth), this->y, (this->z + height));
      glEnd();

      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(this->x, ( this->y + width), (this->z + height));
      glVertex3f(this->x, ( this->y + width), this->z);
      glVertex3f((this->x + this->depth), ( this->y + width), this->z);
      glVertex3f((this->x + this->depth), ( this->y + width), (this->z + height));
      glEnd();

      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(this->x , this->y, (this->z + height));
      glVertex3f(this->x, this->y, this->z);
      glVertex3f(this->x, ( this->y + width), this->z);
      glVertex3f(this->x, ( this->y + width), (this->z + height));
      glEnd();

      glBegin(GL_TRIANGLE_FAN);
      glVertex3f((this->x + this->depth) , this->y, (this->z + height));
      glVertex3f((this->x + this->depth) , this->y, this->z);
      glVertex3f((this->x + this->depth) , ( this->y + width), this->z);
      glVertex3f((this->x + this->depth) , ( this->y + width), (this->z + height));
      glEnd();
    }

};
