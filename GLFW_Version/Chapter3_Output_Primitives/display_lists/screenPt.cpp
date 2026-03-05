#include "screenPt.h"


screenPt::screenPt(void)
{
	this->x = this->y = 0;
}

void screenPt::setCoords(GLint xCoord, GLint yCoord)
{
	this->x = xCoord;
	this->y = yCoord;
}

GLint screenPt::getx(void) const
{
	return this->x;
}

GLint screenPt::gety(void) const
{
	return this->y;
}
