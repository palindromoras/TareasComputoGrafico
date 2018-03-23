#include "SierpinskyGasket.h"



SierpinskyGasket::SierpinskyGasket()
{
}
void SierpinskyGasket::generate(Vec3 a, Vec3 b, Vec3 c, int subdiv)
{
	if (subdiv == 0) {
		vertices.push_back(a);
		vertices.push_back(b);
		vertices.push_back(c);
	}
	else
	{
		Vec3 ab = midPoint(a, b), bc = midPoint(b, c), ca = midPoint(c, a);
		generate(a, ab, ca, subdiv - 1);
		generate(ab, b, bc, subdiv - 1);
		generate(ca, bc, c, subdiv - 1);
	}
}

Vec3 SierpinskyGasket::midPoint(const Vec3& punto1, const Vec3& punto2) {
	Vec3 result(0, 0);
	result.a[0] = (punto1.a[0] + punto2.a[0]) / 2;
	result.a[1] = (punto1.a[1] + punto2.a[1]) / 2;
	result.a[2] = 0;
	return result;
}

SierpinskyGasket::~SierpinskyGasket()
{
}
