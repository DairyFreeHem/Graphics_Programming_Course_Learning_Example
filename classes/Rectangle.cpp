#include <iostream>
#include <GL/glut.h>
#include <vector>

// Rectangle class built in CCW rotation

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
        }
};

class Rectangle
{
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
            return  *this;
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