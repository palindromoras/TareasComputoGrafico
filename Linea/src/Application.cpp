#include "Application.h"


Application::Application()
{
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
	int deg2rad = 3.1416 / 180;
	int rad = 300;
	for (int angle = 0; angle <= 360; angle++) {
		int x = rad * cos(angle*3.1416 / 180);
		int y = rad * (-sin(angle*3.1416 / 180));		
		line(WIDTH / 2, HEIGHT / 2, x + WIDTH / 2, y + HEIGHT / 2);
	}

}
void Application::setup()
{
	angle = 0;
}
