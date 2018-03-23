

#include "stdafx.h"
#include "Application.h"


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
	for (int a = 0; a < 1023; a++) {
		for (int b = 0; b < 1023; b++) {
			putPixel(a, b, 0, 0, 0, 0);
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
	//angle++;
}
void Application::draw()
{
	clearscren();
	int rad = 300;
	float grados = 360.0f /(float) lados;
	for (float angle = 0; angle <= 360; angle+=grados) {
		int x = rad * cos(angle*3.1416 / 180.0f);
		int y = rad * (sin(angle*3.1416 / 180.0f));
		lineto(x + 512, y + 512);
	}
}
void Application::setup()
{

	std::cout << "ingresa el numero de lados de la figura (3-360)" << std::endl;
	std::cin >> lados;
}