#include "Mat4.h"



Mat4::Mat4()
{
	b[0][0] = 1;
	b[0][1] = 0;
	b[0][2] = 0;
	b[0][3] = 0;
	b[1][0] = 0;
	b[1][1] = 1;
	b[1][2] = 0;
	b[1][3] = 0;
	b[2][0] = 0;
	b[2][1] = 1;
	b[2][2] = 0;
	b[2][3] = 0;
	b[3][0] = 0;
	b[3][1] = 0;
	b[3][2] = 0;
	b[3][3] = 1;
}

Mat4 Mat4::Trasladar(const float& Transx, const float& Transy, const float& Transz) {
	Mat4 Matriz;
	Matriz.b[0][0] = 1;
	Matriz.b[0][1] = 0;
	Matriz.b[0][2] = 0;
	Matriz.b[0][3] = Transx;
	Matriz.b[1][0] = 0;
	Matriz.b[1][1] = 1;
	Matriz.b[1][2] = 0;
	Matriz.b[1][3] = Transy;
	Matriz.b[2][0] = 0;
	Matriz.b[2][1] = 0;
	Matriz.b[2][2] = 1;
	Matriz.b[2][3] = Transz;
	Matriz.b[3][0] = 0;
	Matriz.b[3][1] = 0;
	Matriz.b[3][2] = 0;
	Matriz.b[3][3] = 1;
	

	return Matriz;
}
Mat4 Mat4::RotarZ(const float& RotarAnguloZ) {
	Mat4 Matriz;
	Matriz.b[0][0] = cos(RotarAnguloZ*3.1416 / 180.0);
	Matriz.b[0][1] = -sin(RotarAnguloZ*3.1416 / 180.0);
	Matriz.b[0][2] = 0;
	Matriz.b[0][3] = 0;
	Matriz.b[1][0] = sin(RotarAnguloZ*3.1416 / 180.0);
	Matriz.b[1][1] = cos(RotarAnguloZ*3.1416 / 180.0);
	Matriz.b[1][2] = 0;
	Matriz.b[1][3] = 0;
	Matriz.b[2][0] = 0;
	Matriz.b[2][1] = 0;
	Matriz.b[2][2] = 1;
	Matriz.b[2][3] = 0;
	Matriz.b[3][0] = 0;
	Matriz.b[3][1] = 0;
	Matriz.b[3][2] = 0;
	Matriz.b[3][3] = 1;
	return Matriz;
}
Mat4 Mat4::RotarX(const float& RotarAnguloX) {
	Mat4 Matriz;
	Matriz.b[0][0] = 1; 
	Matriz.b[0][1] = 0; 
	Matriz.b[0][2] = 0;
	Matriz.b[0][3] = 0;
	Matriz.b[1][0] = 0; 
	Matriz.b[1][1] = cos(RotarAnguloX*3.1416 / 180.0);
	Matriz.b[1][2] = -sin(RotarAnguloX*3.1416 / 180.0);
	Matriz.b[1][3] = 0;
	Matriz.b[2][0] = 0;
	Matriz.b[2][1] = sin(RotarAnguloX*3.1416 / 180.0);
	Matriz.b[2][2] = cos(RotarAnguloX*3.1416 / 180.0);
	Matriz.b[2][3] = 0;
	Matriz.b[3][0] = 0;
	Matriz.b[3][1] = 0;
	Matriz.b[3][2] = 0;
	Matriz.b[3][3] = 1;
	return Matriz;
}
Mat4 Mat4::RotarY(const float& RotarAnguloY) {
	Mat4 Matriz;
	Matriz.b[0][0] = cos(RotarAnguloY*3.1416 / 180.0);
	Matriz.b[0][1] = 0;
	Matriz.b[0][2] = sin(RotarAnguloY*3.1416 / 180.0);
	Matriz.b[0][3] = 0;
	Matriz.b[1][0] = 0;
	Matriz.b[1][1] = 1;
	Matriz.b[1][2] = 0;
	Matriz.b[1][3] = 0;
	Matriz.b[2][0] = -sin(RotarAnguloY*3.1416 / 180.0);;
	Matriz.b[2][1] = 0;
	Matriz.b[2][2] = cos(RotarAnguloY*3.1416 / 180.0);;
	Matriz.b[2][3] = 0;
	Matriz.b[3][0] = 0;
	Matriz.b[3][1] = 0;
	Matriz.b[3][2] = 0;
	Matriz.b[3][3] = 1;
	return Matriz;
}
Mat4 Mat4::Escalar(const Vec4 Escala) {
	Mat4 Matriz;
	Matriz.b[0][0] = Escala.b[0];
	Matriz.b[0][1] = 0;
	Matriz.b[0][2] = 0;
	Matriz.b[0][3] = 0;
	Matriz.b[1][0] = 0;
	Matriz.b[1][1] = Escala.b[1];
	Matriz.b[1][2] = 0;
	Matriz.b[1][3] = 0;
	Matriz.b[2][0] = 0;
	Matriz.b[2][1] = 0;
	Matriz.b[2][2] = Escala.b[2];
	Matriz.b[2][3] = 0;
	Matriz.b[3][0] = 0;
	Matriz.b[3][1] = 0;
	Matriz.b[3][2] = 0;
	Matriz.b[3][3] = 1;
	return Matriz;
}
Vec4 Mat4::operator*(const Vec4& Vecmultiplicado) const {
	Vec4 regresar(0,0,0);
	regresar.b[0] = (b[0][0] * Vecmultiplicado.b[0]) + (b[0][1] * Vecmultiplicado.b[1]) + (b[0][2] * Vecmultiplicado.b[2])+(b[0][3] * Vecmultiplicado.b[3]);
	regresar.b[1] = (b[1][0] * Vecmultiplicado.b[0]) + (b[1][1] * Vecmultiplicado.b[1]) + (b[1][2] * Vecmultiplicado.b[2])+(b[1][3] * Vecmultiplicado.b[3]);
	regresar.b[2] = (b[2][0] * Vecmultiplicado.b[0]) + (b[2][1] * Vecmultiplicado.b[1]) + (b[2][2] * Vecmultiplicado.b[2])+(b[2][3] * Vecmultiplicado.b[3]);
	regresar.b[3] = (b[3][0] * Vecmultiplicado.b[0]) + (b[3][1] * Vecmultiplicado.b[1]) + (b[3][2] * Vecmultiplicado.b[2])+(b[3][3] * Vecmultiplicado.b[3]);
	return regresar;
}
//(b[][] * MatrizMultiplicada.b[][]) + (b[][] * MatrizMultiplicada.b[][]) + (b[][] * MatrizMultiplicada.b[][]) + (b[][] * MatrizMultiplicada.b[][])
Mat4 Mat4::operator*(const Mat4& MatrizMultiplicada) const {
	Mat4 regresar;
	regresar.b[0][0] = (b[0][0] * MatrizMultiplicada.b[0][0]) + (b[0][1] * MatrizMultiplicada.b[1][0]) + (b[0][2] * MatrizMultiplicada.b[2][0]) + (b[0][3] * MatrizMultiplicada.b[3][0]);
	regresar.b[0][1] = (b[0][0] * MatrizMultiplicada.b[0][1]) + (b[0][1] * MatrizMultiplicada.b[1][1]) + (b[0][2] * MatrizMultiplicada.b[2][1]) + (b[0][3] * MatrizMultiplicada.b[3][1]);
	regresar.b[0][2] = (b[0][0] * MatrizMultiplicada.b[0][2]) + (b[0][1] * MatrizMultiplicada.b[1][2]) + (b[0][2] * MatrizMultiplicada.b[2][2]) + (b[0][3] * MatrizMultiplicada.b[3][2]);
	regresar.b[0][3] = (b[0][0] * MatrizMultiplicada.b[0][3]) + (b[0][1] * MatrizMultiplicada.b[1][3]) + (b[0][2] * MatrizMultiplicada.b[2][3]) + (b[0][3] * MatrizMultiplicada.b[3][3]);
	regresar.b[1][0] = (b[1][0] * MatrizMultiplicada.b[0][0]) + (b[1][1] * MatrizMultiplicada.b[1][0]) + (b[1][2] * MatrizMultiplicada.b[2][0]) + (b[1][3] * MatrizMultiplicada.b[3][0]);
	regresar.b[1][1] = (b[1][0] * MatrizMultiplicada.b[0][1]) + (b[1][1] * MatrizMultiplicada.b[1][1]) + (b[1][2] * MatrizMultiplicada.b[2][1]) + (b[1][3] * MatrizMultiplicada.b[3][1]);
	regresar.b[1][2] = (b[1][0] * MatrizMultiplicada.b[0][2]) + (b[1][1] * MatrizMultiplicada.b[1][2]) + (b[1][2] * MatrizMultiplicada.b[2][2]) + (b[1][3] * MatrizMultiplicada.b[3][2]);
	regresar.b[1][3] = (b[1][0] * MatrizMultiplicada.b[0][3]) + (b[1][1] * MatrizMultiplicada.b[1][3]) + (b[1][2] * MatrizMultiplicada.b[2][3]) + (b[1][3] * MatrizMultiplicada.b[3][3]);
	regresar.b[2][0] = (b[2][0] * MatrizMultiplicada.b[0][0]) + (b[2][1] * MatrizMultiplicada.b[1][0]) + (b[2][2] * MatrizMultiplicada.b[2][0]) + (b[2][3] * MatrizMultiplicada.b[3][0]);
	regresar.b[2][1] = (b[2][0] * MatrizMultiplicada.b[0][1]) + (b[2][1] * MatrizMultiplicada.b[1][1]) + (b[2][2] * MatrizMultiplicada.b[2][1]) + (b[2][3] * MatrizMultiplicada.b[3][1]);
	regresar.b[2][2] = (b[2][0] * MatrizMultiplicada.b[0][2]) + (b[2][1] * MatrizMultiplicada.b[1][2]) + (b[2][2] * MatrizMultiplicada.b[2][2]) + (b[2][3] * MatrizMultiplicada.b[3][2]);
	regresar.b[2][3] = (b[2][0] * MatrizMultiplicada.b[0][3]) + (b[2][1] * MatrizMultiplicada.b[1][3]) + (b[2][2] * MatrizMultiplicada.b[2][3]) + (b[2][3] * MatrizMultiplicada.b[3][3]);
	regresar.b[3][0] = (b[3][0] * MatrizMultiplicada.b[0][0]) + (b[3][1] * MatrizMultiplicada.b[1][0]) + (b[3][2] * MatrizMultiplicada.b[2][0]) + (b[3][3] * MatrizMultiplicada.b[3][0]);
	regresar.b[3][1] = (b[3][0] * MatrizMultiplicada.b[0][1]) + (b[3][1] * MatrizMultiplicada.b[1][1]) + (b[3][2] * MatrizMultiplicada.b[2][1]) + (b[3][3] * MatrizMultiplicada.b[3][1]);
	regresar.b[3][2] = (b[3][0] * MatrizMultiplicada.b[0][2]) + (b[3][1] * MatrizMultiplicada.b[1][2]) + (b[3][2] * MatrizMultiplicada.b[2][2]) + (b[3][3] * MatrizMultiplicada.b[3][2]);
	regresar.b[3][3] = (b[3][0] * MatrizMultiplicada.b[0][3]) + (b[3][1] * MatrizMultiplicada.b[1][3]) + (b[3][2] * MatrizMultiplicada.b[2][3]) + (b[3][3] * MatrizMultiplicada.b[3][3]);
	return regresar;
}
//Mat4 Mat4::LookAt(const Vec4& Eye, const Vec4& Target, const Vec4& Up) {

//}

Mat4::~Mat4()
{
}
