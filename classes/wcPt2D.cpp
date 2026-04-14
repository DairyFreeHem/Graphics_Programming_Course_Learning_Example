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