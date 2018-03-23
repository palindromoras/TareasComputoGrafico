#pragma once
#include "Vec4.h"
#include <math.h>

class Mat4
{
public:
	float b[4][4]; //leerindice
	static Mat4 Trasladar(const float& Transx, const float& Transy, const float& Transz);
	static Mat4 RotarX(const float& RotarAnguloX);
	static Mat4 RotarY(const float& RotarAnguloY);
	static Mat4 RotarZ(const float& RotarAnguloZ);
	static Mat4 Escalar(const Vec4 Escala);
	Vec4 operator* (const Vec4& Vecmultiplicado) const;
	Mat4 operator* (const Mat4& MatrizMultiplicada) const;
	Mat4();
	//static Mat4 LookAt(const Vec4& Eye, const Vec4& Target, const Vec4& Up);
	~Mat4();
};

