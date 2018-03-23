#pragma once
#include "BaseApplication.h"
#include "Vec3.h"
#include "Mat3.h"
#include "SierpinskyGasket.h"
class Application:public BaseApplication
{
public:
	enum Tipo {
		Triangulos, Puntos};
	void drawGeometry(const std::vector<Vec3>& Vertice, Tipo Dibujo);
	float posicionX;
	float posicionY;
	float angulo = 0;
	int lados = 0;
	void clearscren();
	void moveto(float x, float y);
	void lineto(float x, float y);
	int angle;
	void setup() override;
	void sada();
	void update() override;
	void draw() override;
	Application();
	~Application();
	SierpinskyGasket SG;
	std::vector<Vec3> Vcopy;

};

