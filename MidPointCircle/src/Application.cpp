

#include "stdafx.h"
#include "Application.h"


void Application::drawGeometry(const std::vector<Vec4>& Vertice, Tipo Dibujo)
{
	switch (Dibujo) //Qué voy a dibujar? 
	{
	case Application::Triangulos: 
		if (Vertice.size() <= 0) {
			return;
		}
		for (int i = 0; i < Vertice.size(); i += 3) {
			moveto(Vertice[i].b[0], Vertice[i].b[1]);
			lineto(Vertice[i + 1].b[0], Vertice[i + 1].b[1]);
			lineto(Vertice[i + 2].b[0], Vertice[i + 2].b[1]);
			lineto(Vertice[i].b[0], Vertice[i].b[1]);
		}

		break;
	case Application::Puntos:
		for (int a = 0; a < Vertice.size(); a++) {
			putPixel(Vertice[a].b[0], Vertice[a].b[1], 180, 255, 25, 255);
		}
		break;
	default:
		break;
	}
}

Application::Application(){
}

void Application::moveto(float x, float y) {
	posicionX = x;
	posicionY = y;
}

void Application::lineto(float x, float y) {
	line(posicionX, posicionY, x, y);
	moveto(x, y);
}

void Application::clearscren() {
	for (int a = 0; a < WIDTH; a++) {
		for (int b = 0; b < HEIGHT; b++) {
			putPixel(a-WIDTH/2, b-HEIGHT/2, 0, 0, 0, 0);
		}
	}
}
void Application::CrearCirculos(int PosX, int PosY, int Radio) {
	int X = 0;
	int Y = Radio;
	int A = 1 - Radio;
	while (X < Y)
	{
		putPixel(X + PosX, -Y + PosY, 255, 226, 61, 255);
		putPixel(X + PosX, Y + PosY, 255, 226, 61, 255);
		putPixel(-X + PosX, -Y + PosY, 255, 226, 61, 255);
		putPixel(-X + PosX, Y + PosY, 255, 226, 61, 255);
		putPixel(-Y + PosX, X + PosY, 255, 226, 61, 255);
		putPixel(Y + PosX, X + PosY, 255, 226, 61, 255);
		putPixel(-Y + PosX, -X + PosY, 255, 226, 61, 255);
		putPixel(Y + PosX, -X + PosY, 255, 226, 61, 255);

		if (A < 0) {
			A += 2 * X;
		}
		else {
			Y--;
			A += 2 * X - 2 * Y;
		}
		X++;
	}
}


Application::~Application()
{
}

void Application::update()
{
	++angulo;
	Mat4 Rotarz = Mat4::RotarZ(angulo);
	Vec4 T1(300, 0, 0);
	Vec4 Escala(0.5, 0.5, 0.5);
	Mat4 Traslado = Mat4::Trasladar(T1.b[0], T1.b[1], T1.b[2]);
	Mat4 Rotarx = Mat4::RotarX(angulo * 5);
	Mat4 Rotary = Mat4::RotarY(angulo / 10);
	Mat4 escalo = Mat4::Escalar(Escala);
	Mat4 Acumulado = Rotarz*Traslado*Rotarx*Rotary*escalo;
	Mat4 Identidad;
	Vcopy2.clear();
	for (int i = 0; i < Vcopy.size(); i++) {
		Vcopy2.push_back(Acumulado*Vcopy[i]);
	}
}
void Application::draw()
{
	clearscren();
	CrearCirculos(posx1, posy1, radio1);
	CrearCirculos(posx2, posy2, radio2);
	CrearCirculos(posx3, posy3, radio3);
	CrearCirculos(posx4, posy4, radio4);
	CrearCirculos(posx5, posy5, radio5);
	CrearCirculos(posx6, posy6, radio6);
	CrearCirculos(posx7, posy7, radio7);
	CrearCirculos(posx8, posy8, radio8);
	CrearCirculos(posx9, posy9, radio9);
	CrearCirculos(posx10, posy10, radio10);
	CrearCirculos(posx11, posy11, radio11);
	CrearCirculos(posx12, posy12, radio12);
	CrearCirculos(posx13, posy13, radio13);
	CrearCirculos(posx14, posy14, radio14);
	CrearCirculos(posx15, posy15, radio15);
	

	//drawGeometry(Vcopy2, Triangulos);

}
void Application::setup()
{
	Vec4 a(-150, -150, 150), b(150, -150, 150), c(-150, 150, 150), d(150, 150, 150), e(-150, -150, -150), f(150, -150, -150), g(-150, 150, -150), h(150, 150, -150);
	Vcopy.push_back(a);
	Vcopy.push_back(b);
	Vcopy.push_back(c);
	Vcopy.push_back(b);
	Vcopy.push_back(c);
	Vcopy.push_back(d);
	Vcopy.push_back(b);
	Vcopy.push_back(f);
	Vcopy.push_back(d);
	Vcopy.push_back(f);
	Vcopy.push_back(d);
	Vcopy.push_back(h);
	Vcopy.push_back(f);
	Vcopy.push_back(e);
	Vcopy.push_back(h);
	Vcopy.push_back(e);
	Vcopy.push_back(g);
	Vcopy.push_back(h);
	Vcopy.push_back(a);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(g);
	Vcopy.push_back(e);
	Vcopy.push_back(a);
	Vcopy.push_back(b);
	Vcopy.push_back(b);
	Vcopy.push_back(f);
	Vcopy.push_back(e);
	Vcopy.push_back(c);
	Vcopy.push_back(d);
	Vcopy.push_back(g);
	Vcopy.push_back(d);
	Vcopy.push_back(h);
	Vcopy.push_back(g);

	posx1 = rand() % 512; //cambiar el 100 por width/2 o heigth /2 o -witdh /2 o -height /2
	posx2 = rand() % 512;
	posx3 = rand() % 512;
	posx4 = rand() % 512;
	posx5 = rand() % 512;
	posx6 = rand() % 512;
	posx7 = rand() % 512;
	posx8 = rand() % 512;
	posx9 = rand() % 512;
	posx10 = rand() % 512;
	posx11 = rand() % 512;
	posx12 = rand() % 512;
	posx13 = rand() % 512;
	posx14 = rand() % 512;
	posx15 = rand() % 512;

	posy1 = rand() % -512; //cambiar el 100 por width/2 o heigth /2 o -witdh /2 o -height /2
	posy2 = rand() % 512;
	posy3 = rand() % -512;
	posy4 = rand() % 512;
	posy5 = rand() % 512;
	posy6 = rand() % -512;
	posy7 = rand() % -512;
	posy8 = rand() % -512;
	posy9 = rand() % 512;
	posy10 = rand() % 512;
	posy11 = rand() % 512;
	posy12 = rand() % 512;
	posy13 = rand() % -512;
	posy14 = rand() % -512;
	posy15 = rand() % -512;

	radio1 = rand() % 43; 
	radio2 = rand() % 32;
	radio3 = rand() % 21;
	radio4 = rand() % 10;
	radio5 = rand() % 89;
	radio6 = rand() % 11;
	radio7 = rand() % 22;
	radio8 = rand() % 33;
	radio9 = rand() % 44;
	radio10 = rand() % 55;
	radio11 = rand() % 66;
	radio12 = rand() % 77;
	radio13 = rand() % 88;
	radio14 = rand() %  99;
	radio15 = rand() % 100;

	
}