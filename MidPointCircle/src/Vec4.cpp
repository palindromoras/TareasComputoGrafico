#include "Vec4.h"



Vec4::Vec4(float p1, float p2, float p3)
{
	b[0] = p1;
	b[1] = p2;
	b[2] = p3;
	b[3] = 1;
}
Vec4::Vec4() {
	b[0] = 0;
	b[1] = 0;
	b[2] = 0;
	b[3] = 1;
}

Vec4::~Vec4()
{
}
