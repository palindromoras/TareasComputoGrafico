#pragma once
#include <math.h>
#include "Vec3.h"
class Mat3
{
public:
	Mat3();
	~Mat3();
	float a[3][3];
	Mat3(float b);
	static Mat3& Trasladar(const float& Transx, const float& Transy);
	static Mat3& Rotar(const float& RotarAngulo);
	static Mat3& Escalar(const float& Escx, const float& Escy);
	Vec3& operator* (const Vec3& Vecmultiplicado) const;
	Mat3& operator* (const Mat3& MatrizMultiplicada) const;
	
};

