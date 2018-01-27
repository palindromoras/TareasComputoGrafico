#include "Application.h"


Application::Application()
{
}


Application::~Application()
{
}

void Application::update()
{

}
void Application::draw()
{
	for (int x = 0; x < WIDTH; x++) {
		putPixel(x, HEIGHT / 2, 255, 255, 0, 255);
		putPixel(512, x, 150, 150, 255, 0);
		putPixel(x,x, 150, 150, 255, 0);
		putPixel(x, HEIGHT - x, 255, 255, 0, 255);
	}
}
void Application::setup()
{

}
