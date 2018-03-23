#include "Mat3.h"



Mat3::Mat3()
{
	a[0][0] = 1;
	a[0][1] = 0;
	a[0][2] = 0;
	a[1][0] = 0;
	a[1][1] = 1;
	a[1][2] = 0;
	a[2][0] = 0;
	a[2][1] = 0;
	a[2][2] = 1;
}
Mat3::Mat3(float b)
{
	a[0][0] = b;
	a[0][1] = 0;
	a[0][2] = 0;
	a[1][0] = 0;
	a[1][1] = b;
	a[1][2] = 0;
	a[2][0] = 0;
	a[2][1] = 0;
	a[2][2] = b;
	
 }
Mat3& Mat3::Trasladar(const float& Transx, const float& Transy) {
	Mat3 Matriz;
	Matriz.a[0][0] = 1;
	Matriz.a[0][1] = 0;
	Matriz.a[0][2] = Transx;
	Matriz.a[1][0] = 0;
	Matriz.a[1][1] = 1;
	Matriz.a[1][2] = Transy;
	Matriz.a[2][0] = 0;
	Matriz.a[2][1] = 0;
	Matriz.a[2][2] = 1;
	return Matriz;
}
Mat3& Mat3::Rotar(const float& RotarAngulo) {
	Mat3 Matriz;
	Matriz.a[0][0] = cos(RotarAngulo*3.1416 / 180.0);
	Matriz.a[0][1] = -sin(RotarAngulo*3.1416 / 180.0);
	Matriz.a[0][2] = 0;
	Matriz.a[1][0] = sin(RotarAngulo*3.1416 / 180.0);
	Matriz.a[1][1] = cos(RotarAngulo*3.1416 / 180.0);
	Matriz.a[1][2] = 0;
	Matriz.a[2][0] = 0;
	Matriz.a[2][1] = 0;
	Matriz.a[2][2] = 1;
	return Matriz;
}
Mat3& Mat3::Escalar(const float& Escx, const float& Escy) {
	Mat3 Matriz;
	Matriz.a[0][0] = Escx;
	Matriz.a[0][1] = 0;
	Matriz.a[0][2] = 0;
	Matriz.a[1][0] = 0;
	Matriz.a[1][1] = Escy;
	Matriz.a[1][2] = 0;
	Matriz.a[2][0] = 0;
	Matriz.a[2][1] = 0;
	Matriz.a[2][2] = 1;
	return Matriz;
}
Vec3& Mat3::operator*(const Vec3& Vecmultiplicado) const {
	Vec3 regresar(0, 0);
	regresar.a[0] = (a[0][0] * Vecmultiplicado.a[0]) + (a[0][1] * Vecmultiplicado.a[1]) + (a[0][2] * Vecmultiplicado.a[2]);
	regresar.a[1] = (a[1][0] * Vecmultiplicado.a[0]) + (a[1][1] * Vecmultiplicado.a[1]) + (a[1][2] * Vecmultiplicado.a[2]);
	regresar.a[2] = (a[2][0] * Vecmultiplicado.a[0]) + (a[2][1] * Vecmultiplicado.a[1]) + (a[2][2] * Vecmultiplicado.a[2]);
	return regresar;
}
Mat3& Mat3::operator*(const Mat3& MatrizMultiplicada) const {
	Mat3 regresar;
	/*
	[0,0  0,1  0,2] [0,0  0,1  0,2] [(0,0*0,0)+(0,1*1,0)+(0,2*2,0)  (0,0*0,1)+(0,1*1,1)+(0,2*2,1)  (0,0*0,2)+(0,1*1,2)+(0,2*2,2)]
	[1,0  1,1  1,2]*[1,0  1,1  1,2]=[(1,0*0,0)+(1,1*1,0)+(1,2*2,0)  (1,0*0,1)+(1,1*1,1)+(1,2*2,1)  (1,0*0,2)+(1,1*1,2)+(1,2*2,2)]
	[2,0  2,1  2,2] [2,0  2,1  2,2] [(2,0*0,0)+(2,1*1,0)+(2,2*2,0)  (2,0*0,1)+(2,1*1,1)+(0,2*2,1)  (2,0*0,2)+(2,1*1,2)+(2,2*2,2)]
	*/
	regresar.a[0][0] = (a[0][0] * MatrizMultiplicada.a[0][0]) + (a[0][1] * MatrizMultiplicada.a[1][0]) + (a[0][2] * MatrizMultiplicada.a[2][0]);
	regresar.a[0][1] = (a[0][0] * MatrizMultiplicada.a[0][1]) + (a[0][1] * MatrizMultiplicada.a[1][1]) + (a[0][2] * MatrizMultiplicada.a[2][1]);
	regresar.a[0][2] = (a[0][0] * MatrizMultiplicada.a[0][2]) + (a[0][1] * MatrizMultiplicada.a[1][2]) + (a[0][2] * MatrizMultiplicada.a[2][2]);
	regresar.a[1][0] = (a[1][0] * MatrizMultiplicada.a[0][0]) + (a[1][1] * MatrizMultiplicada.a[1][0]) + (a[1][2] * MatrizMultiplicada.a[2][0]);
	regresar.a[1][1] = (a[1][0] * MatrizMultiplicada.a[0][1]) + (a[1][1] * MatrizMultiplicada.a[1][1]) + (a[1][2] * MatrizMultiplicada.a[2][1]);
	regresar.a[1][2] = (a[1][0] * MatrizMultiplicada.a[0][2]) + (a[1][1] * MatrizMultiplicada.a[1][2]) + (a[1][2] * MatrizMultiplicada.a[2][2]);
	regresar.a[2][0] = (a[2][0] * MatrizMultiplicada.a[0][0]) + (a[2][1] * MatrizMultiplicada.a[1][0]) + (a[2][2] * MatrizMultiplicada.a[2][0]);
	regresar.a[2][1] = (a[2][0] * MatrizMultiplicada.a[0][1]) + (a[2][1] * MatrizMultiplicada.a[1][1]) + (a[2][2] * MatrizMultiplicada.a[2][1]);
	regresar.a[2][2] = (a[2][0] * MatrizMultiplicada.a[0][2]) + (a[2][1] * MatrizMultiplicada.a[1][2]) + (a[2][2] * MatrizMultiplicada.a[2][2]);
	return regresar;
}

Mat3::~Mat3()
{
}
