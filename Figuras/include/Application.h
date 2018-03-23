#pragma once
#include "BaseApplication.h"

class Application:public BaseApplication
{
public:
	float posicionX = 512;
	float posicionY;
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


};

