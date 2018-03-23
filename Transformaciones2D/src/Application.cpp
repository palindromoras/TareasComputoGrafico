

#include "stdafx.h"
#include "Application.h"


void Application::drawGeometry(const std::vector<Vec3>& Vertice, Tipo Dibujo)
{
	switch (Dibujo) //Qué voy a dibujar? 
	{
	case Application::Triangulos: 
		if (Vertice.size() <= 0) {
			return;
		}
		for (int i = 0; i < Vertice.size(); i += 3) {
			moveto(Vertice[i].a[0], Vertice[i].a[1]);
			lineto(Vertice[i + 1].a[0], Vertice[i + 1].a[1]);
			lineto(Vertice[i + 2].a[0], Vertice[i + 2].a[1]);
			lineto(Vertice[i].a[0], Vertice[i].a[1]);
		}

		break;
	case Application::Puntos:
		for (int a = 0; a < Vertice.size(); a++) {
			putPixel(Vertice[a].a[0], Vertice[a].a[1], 180, 255, 25, 255);
		}
		break;
	default:
		break;
	}
}
Application::Application()
{
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

void Application::sada() {

}

Application::~Application()
{
}

void Application::update()
{
	Mat3 MatrizRotSiMismo = Mat3::Rotar(angulo);
	Mat3 MatrizTraslacion = Mat3::Trasladar(120, 0);
	Mat3 MatrizR = Mat3::Rotar(angulo);
	Mat3 Acumulado = MatrizTraslacion*MatrizR;
	Mat3 MatrizEscala = Mat3::Escalar(2, 2);
	Vcopy.clear();
	for (int i = 0; i < SG.vertices.size(); i++) {
		Vcopy.push_back(Vec3(MatrizEscala*SG.vertices[i]));
	}
	angulo++;
}
void Application::draw()
{
	clearscren();
	drawGeometry(Vcopy, Triangulos);

}
void Application::setup()
{
	Vec3 a(0, -100), b(100, 100), c(-100, 100);
	SG.generate(a, b, c, 2);

	
}