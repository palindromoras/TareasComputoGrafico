#pragma once
#include "BaseApplication.h"
#include "Vec3.h"
#include "Mat3.h"
#include "SierpinskyGasket.h"
#include "Vec4.h"
#include "Mat4.h"
class Application:public BaseApplication
{
public:
	enum Tipo {
		Triangulos, Puntos,LINEA, LineaStrip, LINELOOP, TRIANGLESTRIP, TRIANGLEFAN};
	void drawGeometry(const std::vector<Vec4>& Vertice, Tipo Dibujo);
	float posicionX;
	float posicionY;
	float angulo = 0;
	int lados = 0;
	void clearscren();
	void moveto(float x, float y);
	void lineto(float x, float y);
	int angle;
	void setup() override;
	void update() override;
	void draw() override;
	Application();
	~Application();
	SierpinskyGasket SG;
	std::vector<Vec4> Vcopy;
	std::vector<Vec4> Vcopy2;
	std::vector<Vec4> linea;
	std::vector<Vec4> LineStrip;
	std::vector<Vec4> LineLoop;
	std::vector<Vec4> TriangleFan;
	std::vector<Vec4> TriangleStrip;

	Vec4 a, b, c, d, e, f, g, h;

};

