#pragma once
#include <GL/freeglut.h>

class screenPt
{
	private:
		GLint x, y;
	public:
		screenPt(void);
		void setCoords(GLint xCoord, GLint yCoord);
		GLint getx() const;
		GLint gety() const;

};