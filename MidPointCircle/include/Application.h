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
		Triangulos, Puntos};
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
	Vec4 a, b, c, d, e, f, g, h;
	void CrearCirculos(int PosX, int PosY, int Radio);
	int posx1, posy1, radio1;
	int posx2, posy2, radio2;
	int posx3, posy3, radio3;
	int posx4, posy4, radio4;
	int posx5, posy5, radio5;
	int posx6, posy6, radio6;
	int posx7, posy7, radio7;
	int posx8, posy8, radio8;
	int posx9, posy9, radio9;
	int posx10, posy10, radio10;
	int posx11, posy11, radio11;
	int posx12, posy12, radio12;
	int posx13, posy13, radio13;
	int posx14, posy14, radio14;
	int posx15, posy15, radio15;
	

};